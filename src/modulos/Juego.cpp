#include "Juego.h"

Juego::Juego(const Mapa &m) : _mapa(m) {
}

Juego::~Juego() {

}

const Mapa Juego::mapa() const {
    return _mapa;
}





