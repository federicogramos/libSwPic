/*******************************************************************************
 * @file /sys/sys12f_userSettings.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version  20250711 1816
 * 
 * Cada proyecto debe tener su sys12f_userSettings.h particular.
 ******************************************************************************/


 /*******************************************************************************
 * @brief
 ******************************************************************************/

#define UNUSED0	GPIO0
#define LED		GPIO1
#define ACD		GPIO2
#define UNUSED3	GPIO3
#define RLY		GPIO4
#define UNUSED5	GPIO5

/*******************************************************************************
 * @brief
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
                   DDR_LED = OUTPUT;                                           \
                   DDR_RLY = OUTPUT;                                           \
                   DDR_ADC = INPUT;                                            \
                   }