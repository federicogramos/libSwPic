/*******************************************************************************
 * @file kPin_aliases.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version 20251215 1645
 * @note Nombre de keys a usar.
 ******************************************************************************/

#ifndef __KPIN_ALIASES_H
#define __KPIN_ALIASES_H


// Lo unico que necesita para establecer el alias es que el alias sea coincident
// con el nro de elemento del array con el que se invoca el driver del pusador.
enum e_kPinAlias {
	P0N,
	P1N,
	P0P,
	IN_FN,
	IN_FP,
	KPIN_CANT
};


#endif // __KPIN_ALIASES_H
