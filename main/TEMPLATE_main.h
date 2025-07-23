/*******************************************************************************
 * @file /main.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version  20250723 1546
 ******************************************************************************/


#ifndef __MAIN_H
#define __MAIN_H


__CONFIG(CPD & PROTECT & BOREN & MCLRDIS & PWRTEN & WDTDIS & INTIO);
/* data protect on */ 
/* code protection on */
/* brown out reset enabled */
/* master clear reset function disabled */
/* power up timer enabled */
/* watchdog timer disabled */
/* internal osc/GP4 = IO//GP5 = IO */

// La macro que setea los bits de configuracion, debe ser invocada unicamente 1
// sola vez en todo el programa, porque de otro modo, el compilador detecta un
// error.

__IDLOC7(0x20,0x11,0x02,0x22);
// ID Locations son un pequeno espacio de memoria en el cual el usuario puede
// (en tiempo de programacion) almacenar el checksum, informacion de la version
// del programa, o lo que quiera.
// Almaceno la fecha de generacion del HEX. El formato es: ano[2], mes[1],
// dia[1].

#endif // __MAIN_H