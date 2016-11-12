#ifndef TIPOSJUEGO_H_
#define TIPOSJUEGO_H_

#include "aed2/TiposBasicos.h"

using namespace aed2;

typedef unsigned int Jugador;
typedef std::string Pokemon;
 
struct Coordenada
{
	Nat latitud;
	Nat longitud;
	Coordenada(Nat latitud, Nat longitud) : latitud(latitud), longitud(longitud)
	{
	}
};

inline bool operator == (const Coordenada& c1, const Coordenada& c2){
 return c1.latitud == c2.latitud and c1.longitud == c2.longitud;
}

inline bool operator != (const Coordenada& c1, const Coordenada& c2){
 return not (c1 == c2);
}

#endif