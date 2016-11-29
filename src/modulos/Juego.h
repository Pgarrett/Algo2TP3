#ifndef SRC_JUEGO_H
#define SRC_JUEGO_H

#include "Mapa.h"
#include "ColaMinPrior.h"
#include "../aed2/Vector.h"
#include "DiccMat.h"
#include "diccString.h"
#include "../aed2/Lista.h"

class Juego {

public:
    Juego(const Mapa &m);    // CrearJuego
    ~Juego();

/* Agrega el pokemon pasado por parametro en su coordenada al juego. */
    void agregarPokemon(const Pokemon &p, const Coordenada &c);

    /* Agrega un nuevo jugador, asignandole el id correspondiente.
     * Esta función deberá cambiar su aridad respecto del TAD devolviendo:
     * el id del jugador agregado. */
    Jugador agregarJugador();

    /* Al jugador pasado por parametro, lo conecta en la coordenada indicada.
     * Requiere que el jugador este en el juego desconectado ytp
     * que la Coordenada pasada este en el mapa. */
    void conectarse(const Jugador &j, const Coordenada &c);

    /* Al jugador pasado por parametro, lo desconecta.
     * Requiere que el jugador este en el juego conectado. */
    void desconectarse(const Jugador &j);

    /* Al jugador pasado por parametro, lo intenta mover hacia la coordenada indicada.
     * Requiere que el jugador este en el juego conectado y
     * que la Coordenada pasada este en el mapa. */
    void moverse(const Jugador &id, const Coordenada &c);

    /* Devuelve todas las coordenadas que posee el mapa del Juego. */
    const Mapa mapa() const;

    /* Devuelve los jugadores que fueron insertados en el juego y no fueron eliminados. */
    Conj<Jugador> jugadores() const;

    /* Dado el jugador pasado como parametro, retorna si esta conectado o no.
     * Requiere que el jugador este entre jugadores() del juego. */
    bool estaConectado(const Jugador &j) const;

    /* Dado el jugador pasado como parametro, devuelve la cantidad de sanciones que recibio.
     * Requiere que el jugador este entre jugadores() del juego. */
    Nat sanciones(const Jugador &j) const;

    /* Dado el jugador pasado como parametro, devuelve la coordenada donde se ubica.
     * Requiere que el jugador este entre jugadores() del juego y este conectado. */
    Coordenada posicion(const Jugador &j) const;

    /* Dado el jugador pasado como parametro, devuelve un MultiConjunto con los
     * pokemons que capturo.
     * Requiere que el jugador este entre jugadores() del juego. */
    Dicc<Pokemon, Nat> pokemons(const Jugador &j) const;

    /* Devuelve los jugadores que fueron expulsados del juego. */
    Conj<Jugador> expulsados() const;

    /* Devuelve todas las coordenadaes del mapa que tienen un pokemon en ella. */
    Conj<Coordenada> posConPokemons() const;

    /* Dada una coordenada del mapa, devuelve al pokemon situado en ella.
     * Es requisito que la coordenada exista en el mapa y que exista un pokemon alli. */
    Pokemon pokemonEnPos(const Coordenada &c) const;

    /* Dada una coordenada, devuelve el valor del contador de movimientos fuera del rango.
   * Es requisito que en la coordenada pasada como parametro haya un pokemon. */
    Nat cantMovimientosParaCaptura(const Coordenada &c) const;

    /* Dada una coordenada cualquiera, indica si la coordenada existe en el mapa y
     * que hay un pokemon a distancia menor o igual a 5. */

    bool puedoAgregarPokemon(const Coordenada &c) const;

    /* Devuelve si hay un pokemon a distancia menor o igual a 2
     * de la Coordenada pasada como parametro. */
    bool hayPokemonCercano(const Coordenada &c) const;

    /* Dada una Coordenada, devuelve la coordenada del pokemon cercano.
     * Requiere que haya un pokemon a distancia menor o igual a 2. */
    Coordenada posPokemonCercano(const Coordenada &c) const;

    /* Devuelve todos los jugadores que esten a distancia menor o igual a 2 de
     * la coordenada indicada, que tengan un camino hasta ella.
     * Requiere que haya un pokemon a distancia menor o igual a 2 de la Coordenada. */
    Conj<Jugador> entrenadoresPosibles(const Coordenada &c) const;

    /* Devuelve el indice de rarez del pokemon pasado como parametro.
     * Requiere que haya al menos un pokemon de la especie en el juego. */
    Nat indiceRareza(const Pokemon &p) const;

    /* Devuelve la cantidad de pokemons totales en el juego. */
    Nat cantPokemonsTotales() const;

    /* Indica cuantos pokemons de la especie de unPokemon hay en pokemons. */
    Nat cantMismaEspecie(const Pokemon &p) const;

    /* SOLO PARA TEST */
    Lista<Jugador>::const_Iterador jugadoresEnPos(const Coordenada &c) const;

private:

    struct InfoPokemon {
        Pokemon tipo;
        Coordenada posicion;
        Nat contador;
        ColaMinPrior<Lista<Jugador>::Iterador> jugadoresEnRango;
        bool salvaje;

        InfoPokemon(const Pokemon &p, const Coordenada &c) : tipo(p), posicion(c), contador(0),
                                                             jugadoresEnRango(ColaMinPrior<Lista<Jugador>::Iterador>()),
                                                             salvaje(true){}
    };

    struct InfoJugador {
        Conj<Jugador>::Iterador id;
        bool estaConectado;
        Nat sanciones;
        Conj<Lista<InfoPokemon>::Iterador> pokemonesCapturados;
        Coordenada posicion;
        Lista<Jugador>::Iterador itPosicion;
        InfoJugador(Conj<Jugador>::Iterador ID) : id(ID), estaConectado(false), sanciones(0),
                                                  pokemonesCapturados(Conj<Lista<InfoPokemon>::Iterador>()), posicion(Coordenada(0, 0)),
                                                  itPosicion(Lista<Jugador>().CrearIt()) { }
    };

    struct InfoVectorJugadores {
        Lista<InfoJugador>::Iterador info;
        ColaMinPrior<Lista<Jugador>::Iterador>::Iterador encolado;
        InfoVectorJugadores(Lista<InfoJugador>::Iterador i, ColaMinPrior<Lista<Jugador>::Iterador>::Iterador e) : info(i), encolado(e) {}
    };

    Nat DamePos(const Nat p, const Nat step) const;
    Nat DistEuclidea(const Coordenada c1, const Coordenada c2) const;
    bool debeSancionarse(const Jugador j, const Coordenada c) const;
    void AgregarJugadorEnPos(DiccMat<Lista<Jugador> *> &d, InfoJugador &j, Coordenada c);
    bool hayPokemonEnTerritorio(const Coordenada &c) const;
    bool perteneceAPokemons(const Pokemon &p) const;
    void ActualizarPokemon(Lista<InfoPokemon>::Iterador itPokemones);
    void ActualizarTodos();
    void ActualizarMenos(const Coordenada &c);

    Mapa _mapa;
    Lista<InfoJugador> _jugadores;
    Conj<Jugador> _idsJugadores;
    Conj<Jugador> _expulsados;
    Vector<InfoVectorJugadores> _jugadoresPorID;
    DiccString<Nat> _pokemones;
    Lista<InfoPokemon> _todosLosPokemones;
    DiccMat<Lista<InfoPokemon>::Iterador> _posicionesPokemons;
    DiccMat<Lista<Jugador>*> _posicionesJugadores;

};


#endif //SRC_JUEGO_H
