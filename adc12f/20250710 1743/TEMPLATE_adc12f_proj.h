/*******************************************************************************
 * @file /adc12f_proj.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version 20250427 1843
 * @note Seteos específicos del proyecto (adc).
 ******************************************************************************/


#ifndef __IRQ12F_ADC_PROJ_H
#define __IRQ12F_ADC_PROJ_H


/*******************************************************************************
 * @brief Las siguientes deben ser ajustadas segun el uso q se le de al ad.
 ******************************************************************************/

// The ANS3:ANS0 bits (ANSEL<3:0>) and the TRISIO bits control the operation of 
// the A/D port pins. Set the corresponding TRISIO bits to set the pin output dr
// iver to its high-impedance state. Likewise, set the corresponding ANS bit to 
// disable the digital input buffer.
#define ANS0_VAL	DIGITAL_IO
#define ANS1_VAL	DIGITAL_IO
#define ANS2_VAL	DIGITAL_IO
#define ANS3_VAL	ANALOG_INPUT

// Channel selection. There are four analog channels on the PIC12F675, AN0 throu
// gh AN3. The CHS1:CHS0 bits (ADCON0<3:2>) control which channel is connected t
// o the sample and hold circuit.
#define CHS0_VAL	1
#define CHS1_VAL	1

// There are two options for the voltage reference to the A/D converter: either 
// VDD is used, or an analog voltage applied to VREF is used. The VCFG bit (ADCO
// N0<6>) controls the voltage reference selection:
// -- VCFG = 1 voltage on the VREF pin is the reference.
// -- VCFG = 0 VDD is the reference.
#define VCFG_VAL	0

// ADFM: A/D Result Formed Select bit
// The A/D conversion can be supplied in two formats: left or right shifted. The
// ADFM bit (ADCON0<7>) controls the output format.
//                           |     ADRESH      |      ADRESL     |
//                           | 7 6 5 4 3 2 1 0 | 7 6 5 4 3 2 1 0 |
//                           |<- 10 bit ad result ->|            |
// ADFM = 0, left justified  | x x x x x x x x   x x|- - - - - - |
//                                        |<- 10 bit ad result ->|
// ADFM = 1, right justified | - - - - - -|x x   x x x x x x x x |
#define ADFM_VAL	1

// TAD vs. DEVICE OPERATING FREQUENCIES
// Operat  ADCS2:0 20MHz      5MHz       4MHz       1.25MHz
// 2 TOSC  000     100ns(2)   400ns(2)   500ns(2)   1.6us
// 4 TOSC  100     200ns(2)   800ns(2)   1.0us(2)   3.2us
// 8 TOSC  001     400ns(2)   1.6us      2.0us      6.4us
// 16 TOSC 101     800ns(2)   3.2us      4.0us      12.8us(3)
// 32 TOSC 010     1.6us      6.4us      8.0 us(3)  25.6us(3)
// 64 TOSC 110     3.2us      12.8us(3)  16.0us(3)  51.2us(3)
// A/D RC  x11     2-6us(1,4) 2-6us(1,4) 2-6us(1,4) 2-6us(1,4)
#define ADCS0_VAL	1
#define ADCS1_VAL	1
#define ADCS2_VAL	1

// ADON: A/D Conversion Status bit
// 0 = A/D converter is shut-off and consumes no operating current
// 1 = A/D converter module is operating
#define ADON_VAL	1


#endif // __IRQ12F_ADC_PROJ_H