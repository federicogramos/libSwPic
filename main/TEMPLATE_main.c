/*******************************************************************************
 * @file /elevador12f675/sw/main.c
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version  20250710 1747
 ******************************************************************************/


#include <project.h>
#include <project_proj.h>
#include <main.h> // Fuses y otras cosas.
#include <adc12f.h>
#include <t0.h>
#include <sys12f.h> // Para la inicializacion del sistema.


/*******************************************************************************
 * @brief Globals
 ******************************************************************************/

char numeroDisplay = 0; // Esta variable contiene el numero que se muestra en el display de 7 segmentos.




/*******************************************************************************
 * @brief Entry point.
 ******************************************************************************/

void main(void) {

	sys12f_init();

	T0_INIT_LOOP(T0_500MS);

	while(1) {
		if(T0_TIMEOUT(T0_500MS)) {
			if(LED == 0)
				LED = 1;
			else
				LED = 0;
		}

		if(T0_TIMEOUT(T0_ADC)) {
			if(adc12f_val < TH_ON) {
				RLY = 1;
			} else if(adc12f_val > TH_OFF) {
				RLY = 0;
			}
		}
	//numeroDisplay = (adc12f_val / (ADC12F_MAX / 9));
	}

}

