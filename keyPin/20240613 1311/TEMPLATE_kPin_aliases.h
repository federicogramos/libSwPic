//*****************************************************************************
// ARCHIVO: /kPin_aliases.h
// AUTOR: Federico Ramos
// ULT. MODIF: 2022-10-12
// PROYECTO: TMP:11:CIC
//*****************************************************************************


#ifndef __KPIN_ALIASES_H
#define __KPIN_ALIASES_H


//*****************************************************************************
// ALIAS
// LO UNICO QUE NECESITA PARA ESTABLECER EL ALIAS, ES QUE EL ALIAS SEA COINCIDENTE CON EL NRO DE ELEMENTO DEL ARRAY CON EL QUE SE INVOCA EL DRIVER DEL PULSADOR
// Se puede nombrar al alias como FP o FN pero en esta version de libreria kPin, cualquiera de los
// pines puede ser revisado por su cambio de FP o FN por lo que no es necesario explicitar que tal pin sirve para ello,
// sino que tan solo utilizar la macro de  KPIN_EVENT adecuada.
enum e_kPinAlias
    {
	P0N,
	P1N,
	P0P,
	IN_FN,
	IN_FP,
	KPIN_CANT
    };
//*****************************************************************************


#endif//__KPIN_ALIASES_H
