#ifndef SRC_TESTSJUEGO_H
#define SRC_TESTSJUEGO_H

#include "../modulos/Mapa.h"

class TestsJuego {

public:
    static void correr_tests();

private:
    // CrearJuego
    static void test_juego_constructor_con_mapa();

    static void test_juego_crear_juego_sin_jugadores();

    static void test_juego_crear_juego_sin_expulsados();

    static void test_juego_crear_juego_sin_posiciones_con_pokemons();

    // AgregarJugador
    static void test_juego_jugadores_con_id_secuencial();

    static void test_juego_jugador_nuevo_no_modifica_expulsados();

    static void test_juego_jugador_nuevo_desconectado();

    static void test_juego_jugador_nuevo_sin_sanciones();

    static void test_juego_jugador_nuevo_sin_pokemones();

    static void test_juego_hay_pokemon_cercano_coordenada_invalida();

    static void test_juego_hay_pokemon_cercano_coordenada_con_pokemon();

    static void test_juego_hay_pokemon_cercano_coordenada_con_pokemon_cercano();

    static void test_juego_hay_pokemon_cercano_coordenada_con_pokemon_lejano();

    static void test_juego_crear_juego_sin_posiciones_con_jugadores();
};


#endif //SRC_TESTSJUEGO_H
