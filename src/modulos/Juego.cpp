#include "Juego.h"

Juego::Juego(const Mapa &m) : _mapa(m), _jugadores(Conj<InfoJugador>()), _idsJugadores(Conj<Jugador>()), _expulsados(Conj<Jugador>())  {
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

Conj<Jugador> Juego::expulsados() const {
    return _expulsados;
}





