#include "Driver.h"

/*
 *  HAY QUE SACAR EL CHECKEO DE PRECONDICIONES DE LOS MODULOS BASICOS
 */

// Instanciar un mapa y un juego 

Driver::Driver(const Conj<Coordenada> &cs) {
    Mapa m;
    Conj<Coordenada>::const_Iterador itConj = cs.CrearIt();
    while (itConj.HaySiguiente()) {
        m.agregarCoordenada(itConj.Siguiente());
    }
    _juego = new Juego(m);
}

Driver::~Driver() {
    delete _juego;
    _juego = NULL;
}

void Driver::agregarPokemon(const Pokemon &p, const Coordenada &c) {
    _juego->agregarPokemon(p, c);
}

Jugador Driver::agregarJugador() {
    return _juego->agregarJugador();
}

void Driver::conectarse(const Jugador &j, const Coordenada &c) {
    _juego->conectarse(j, c);
}

void Driver::desconectarse(const Jugador &j) {
    _juego->desconectarse(j);
}

void Driver::moverse(const Jugador &j, const Coordenada &c) {
    _juego->moverse(j, c);
}

Conj<Coordenada> Driver::mapa() const {
    return _juego->mapa().coordenadas();
}

bool Driver::hayCamino(const Coordenada &c1, const Coordenada &c2) const {
    return _juego->mapa().hayCamino(c1, c2);
}

bool Driver::posExistente(const Coordenada &c) const {
    return _juego->mapa().posExistente(c);
}

Conj<Jugador> Driver::jugadores() const {
    return _juego->jugadores();
}

bool Driver::estaConectado(const Jugador &j) const {
    return _juego->estaConectado(j);
}

Nat Driver::sanciones(const Jugador &j) const {
    return _juego->sanciones(j);
}

Coordenada Driver::posicion(const Jugador &j) const {
    return _juego->posicion(j);
}

Dicc<Pokemon, Nat> Driver::pokemons(const Jugador &j) const {
    return _juego->pokemons(j);
}

Conj<Jugador> Driver::expulsados() const {
    return _juego->expulsados();
}

Conj<Coordenada> Driver::posConPokemons() const {
    return _juego->posConPokemons();
}

Pokemon Driver::pokemonEnPos(const Coordenada &c) const {
    return _juego->pokemonEnPos(c);
}

Nat Driver::cantMovimientosParaCaptura(const Coordenada &c) const {
    return _juego->cantMovimientosParaCaptura(c);
}

bool Driver::puedoAgregarPokemon(const Coordenada &c) const {
    return _juego->puedoAgregarPokemon(c);
}

bool Driver::hayPokemonCercano(const Coordenada &c) const {
    return _juego->hayPokemonCercano(c);
}

Coordenada Driver::posPokemonCercano(const Coordenada &c) const {
    return _juego->posPokemonCercano(c);
}

Conj<Jugador> Driver::entrenadoresPosibles(const Coordenada &c) const {
    return _juego->entrenadoresPosibles(c);
}

Nat Driver::indiceRareza(const Pokemon &p) const {
  return _juego->indiceRareza(p);
}

Nat Driver::cantPokemonsTotales() const {
    return _juego->cantPokemonsTotales();
}

Nat Driver::cantMismaEspecie(const Pokemon &p) const {
    return _juego->cantMismaEspecie(p);
}


// TODO: Completar con el resto de las implementaciones