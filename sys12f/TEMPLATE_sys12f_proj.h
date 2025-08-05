/*******************************************************************************
 * @file /sys/sys12f_userSettings.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version  20250711 1816
 * @note Cada proyecto debe tener su sys12f_userSettings.h particular.
 ******************************************************************************/


 /******************************************************************************
 * @brief Puertos q se usan e identificación.
 * 
 *                           +-----------+
 *                     VDD ==|    \_/    |== VSS
 *    GP5/T1CKI/OSC1/CLKIN ==| PIC12F675 |== GP0/AN0/CIN+/ICSPDAT
 * GP4/AN3/T1G/OSC2/CLKOUT ==|           |== GP1/AN1/CIN-/VREF/ICSPCLK
 *            GP3/MCLR/VPP ==|           |== GP2/AN2/T0CKI/INT/COUT
 *                           +-----------+
 ******************************************************************************/

#define UNUSED0	GPIO0
#define LED		GPIO1
#define ACD		GPIO2
#define UNUSED3	GPIO3
#define RLY		GPIO4
#define UNUSED5	GPIO5


/*******************************************************************************
 * @brief GPIO data direction registers.
 ******************************************************************************/

#define DDR_UNUSED0	TRIS0
#define DDR_LED		TRIS1
#define DDR_ADC		TRIS2
#define DDR_UNUSED3	TRIS3
#define DDR_RLY		TRIS4
#define DDR_UNUSED5	TRIS5


/*******************************************************************************
 * @brief
 ******************************************************************************/

#define INIT_DDR() {                                                           \
	DDR_LED = OUTPUT;                                                          \
	DDR_RLY = OUTPUT;                                                          \
	DDR_ADC = INPUT;                                                           \
	}

/*******************************************************************************
 * @brief En caso de que se requiere valores iniciales al booteo.
 ******************************************************************************/

#define INIT_PORTS() {                                                         \
	LED = 0;                                                                   \
	RLY = 0;                                                                   \
	}

