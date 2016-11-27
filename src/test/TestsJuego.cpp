#include "TestsJuego.h"
#include "../mini_test.h"
#include "../modulos/Juego.h"

typedef Coordenada Coor;

Mapa crearMapaDefault();

void TestsJuego::correr_tests() {
    // CrearJuego
    RUN_TEST(test_juego_constructor_con_mapa);
    RUN_TEST(test_juego_crear_juego_sin_jugadores);
    RUN_TEST(test_juego_crear_juego_sin_expulsados);

    // AgregarJugador
    RUN_TEST(test_juego_jugadores_con_id_secuencial);
    RUN_TEST(test_juego_jugador_nuevo_no_modifica_expulsados);
    RUN_TEST(test_juego_jugador_nuevo_desconectado);
    RUN_TEST(test_juego_jugador_nuevo_sin_sanciones);

    // Hay pokemons cercano
    RUN_TEST(test_juego_hay_pokemon_cercano_coordenada_invalida);
//    RUN_TEST(test_juego_hay_pokemon_cercano_coordenada_con_pokemon);
//    RUN_TEST(test_juego_hay_pokemon_cercano_coordenada_con_pokemon_cercano);
//    RUN_TEST(test_juego_hay_pokemon_cercano_coordenada_con_pokemon_lejano);
}

Mapa crearMapaDefault() {
    Mapa mapa;
    mapa.agregarCoordenada(Coor(0, 0));
    mapa.agregarCoordenada(Coor(0, 1));
    mapa.agregarCoordenada(Coor(0, 2));
    mapa.agregarCoordenada(Coor(1, 2));
    mapa.agregarCoordenada(Coor(10, 0));
    mapa.agregarCoordenada(Coor(1, 4));
    return mapa;
}

// CrearJuego

void TestsJuego::test_juego_constructor_con_mapa() {
    Mapa mapa = crearMapaDefault();

    Juego j(mapa);

    ASSERT(j.mapa().coordenadas() == mapa.coordenadas());
}

void TestsJuego::test_juego_crear_juego_sin_jugadores() {
    Mapa mapa = crearMapaDefault();

    Juego j(mapa);

    ASSERT(j.jugadores().Cardinal() == 0);
}

void TestsJuego::test_juego_jugadores_con_id_secuencial() {
    Mapa mapa = crearMapaDefault();

    Juego j(mapa);
    ASSERT(j.agregarJugador() == 0);
    ASSERT(j.agregarJugador() == 1);
}

void TestsJuego::test_juego_crear_juego_sin_expulsados() {
    Mapa mapa = crearMapaDefault();

    Juego j(mapa);

    ASSERT(j.expulsados().Cardinal() == 0);
}

void TestsJuego::test_juego_crear_juego_sin_posiciones_con_pokemons() {

}

void TestsJuego::test_juego_crear_juego_sin_posiciones_con_jugadores() {

}

// AgregarJugador
void TestsJuego::test_juego_jugador_nuevo_no_modifica_expulsados() {
    Mapa mapa = crearMapaDefault();

    Juego j(mapa);

    ASSERT(j.expulsados().Cardinal() == 0);
    j.agregarJugador();
    ASSERT(j.expulsados().Cardinal() == 0);
}

void TestsJuego::test_juego_jugador_nuevo_desconectado() {
    Mapa mapa = crearMapaDefault();
    Juego j(mapa);

    Jugador jug = j.agregarJugador();

    ASSERT(not j.estaConectado(jug));
}

void TestsJuego::test_juego_jugador_nuevo_sin_sanciones() {
    Mapa mapa = crearMapaDefault();
    Juego j(mapa);

    Jugador jug = j.agregarJugador();

    ASSERT(j.sanciones(jug) == 0);
}

void TestsJuego::test_juego_jugador_nuevo_sin_pokemones() {
    /* TODO revisar con leticia, la implementacion pide que pokemons devuelva un dicc<pokemon, nat>
    * TODO nosotros no hacemos eso (porque la cagamos cuando diseñanmos)
    */
    Mapa mapa = crearMapaDefault();
    Juego j(mapa);

    Jugador jug = j.agregarJugador();

    ASSERT(j.sanciones(jug) == 0);
}

// Conectarse


// HayPokemonCercano
void TestsJuego::test_juego_hay_pokemon_cercano_coordenada_invalida() {
    Mapa mapa = crearMapaDefault();

    Juego j(mapa);

    ASSERT(not j.hayPokemonCercano(Coor(1, 1)));
}

void TestsJuego::test_juego_hay_pokemon_cercano_coordenada_con_pokemon() {
    Mapa mapa;
    Juego j(mapa);

    j.agregarPokemon("poke", Coor(1, 1));

    ASSERT(j.hayPokemonCercano(Coor(1, 1)));
}

void TestsJuego::test_juego_hay_pokemon_cercano_coordenada_con_pokemon_cercano() {
    Mapa mapa;
    Juego j(mapa);

    j.agregarPokemon("poke", Coor(1, 1));

    ASSERT(j.hayPokemonCercano(Coor(3, 1)));
}

void TestsJuego::test_juego_hay_pokemon_cercano_coordenada_con_pokemon_lejano() {
    Mapa mapa;
    Juego j(mapa);

    j.agregarPokemon("poke", Coor(1, 1));

    ASSERT(not j.hayPokemonCercano(Coor(4, 4)));
}
