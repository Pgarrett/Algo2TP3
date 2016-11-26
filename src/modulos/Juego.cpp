#include "Juego.h"

Juego::Juego(const Mapa &m) : _mapa(m), _jugadores(Conj<InfoJugador>()), _idsJugadores(Conj<Jugador>()), _expulsados(Conj<Jugador>()), _jugadoresPorID(Vector<InfoVectorJugadores>()) {
}

Juego::~Juego() {

}

const Mapa Juego::mapa() const {
    return _mapa;
}

Jugador Juego::agregarJugador() {
    Jugador id =_jugadores.Cardinal() + _expulsados.Cardinal();
    Conj<Jugador>::Iterador itConjIds = _idsJugadores.AgregarRapido(id);
    Conj<InfoJugador>::Iterador itJ = _jugadores.AgregarRapido(InfoJugador(itConjIds));
    _jugadoresPorID.AgregarAtras(InfoVectorJugadores(itJ, ColaMinPrior<Jugador>().CrearIt()));
    return id;
}

Conj<Jugador> Juego::expulsados() const {
    return _expulsados;
}

bool Juego::estaConectado(const Jugador &j) const {
    return _jugadoresPorID.operator[](j).info.Siguiente().estaConectado;
}

Nat Juego::sanciones(const Jugador &j) const {
    return _jugadoresPorID.operator[](j).info.Siguiente().sanciones;
}

Conj<Jugador> Juego::jugadores() const {
    return _idsJugadores;
}

bool Juego::hayPokemonCercano(const Coordenada &c) const {
    return false;
}

void Juego::agregarPokemon(const Pokemon &p, const Coordenada &c) {

}

void Juego::conectarse(const Jugador &j, const Coordenada &c) {

}

void Juego::moverse(const Jugador &j, const Coordenada &c) {

}

Coordenada Juego::posicion(const Jugador &j) const {
    return Coordenada(0, 0);
}

Nat Juego::cantPokemonsTotales() const {
    return 0;
}

Nat Juego::cantMismaEspecie(const Pokemon &p) const {
    return 0;
}





