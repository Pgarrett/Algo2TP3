#include "Juego.h"

Juego::Juego(const Mapa &m) : _mapa(m) {
}

Juego::~Juego() {

}

const Mapa Juego::mapa() const {
    return _mapa;
}

Jugador Juego::agregarJugador() {
    Jugador id =_jugadores.Cardinal() + _expulsados.Cardinal();
    Conj<Jugador>::Iterador itConjIds = _idsJugadores.AgregarRapido(id);
    _jugadores.AgregarRapido(InfoJugador(itConjIds));
    return id;
}





