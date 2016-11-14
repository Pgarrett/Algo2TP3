#include "Mapa.h"

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

Mapa::~Mapa() {
}