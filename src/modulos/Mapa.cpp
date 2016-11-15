#include <stdexcept>
#include "Mapa.h"

typedef Coordenada Coor;
typedef Conj<Coor>::const_Iterador ItConj;

Mapa::Mapa() {
}

void Mapa::agregarCoordenada(const Coordenada &c) {
    coords.Agregar(c);
}

Conj<Coordenada> Mapa::coordenadas() const {
    return coords;
}

bool Mapa::posExistente(const Coordenada &c) const {
    return coords.Pertenece(c);
}

Nat Mapa::ancho() const {
    assert(!coords.EsVacio());
    Nat ancho = 0;
    for(ItConj it = coords.CrearIt(); it.HaySiguiente(); it.Avanzar()){
        Coor c = it.Siguiente();
        if (c.longitud > ancho)
            ancho = c.longitud;
    }
    return ++ancho;
}

Nat Mapa::largo() const {
    assert(!coords.EsVacio());
    Nat largo = 0;
    for(ItConj it = coords.CrearIt(); it.HaySiguiente(); it.Avanzar()){
        Coor c = it.Siguiente();
        if (c.latitud > largo)
            largo = c.latitud;
    }
    return ++largo;
}

Mapa::~Mapa() {
}
