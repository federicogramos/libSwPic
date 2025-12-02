/*******************************************************************************
 * @file /libSwPic/x1wDht11/TEMPLATE_x1wDht11_settings.c
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version  20250923 1729
 * 
 * Seteos que deben ser realizados especificamente para cada proyecto.
 ******************************************************************************/

/*******************************************************************************
 * @brief User-defined objects declared const are placed in a special psect link
 * ed into the program space. Objects qualified const may be absolute. The @ add
 * ress construct is used to place the object at the specified address in progra
 * m memory as in the following example which places the object tableDef at addr
 * ess 0x100.
 * const int tableDef[] @ 0x100 = { 0, 1, 2, 3, 4};
 ******************************************************************************/

volatile bit X1W_DHT11_PIN		@ ((unsigned)&GPIO * 8) + 5;
volatile bit X1W_DHT11_PIN_DDR	@ ((unsigned)&TRISIO * 8) + 5;