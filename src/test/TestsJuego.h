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

    static void test_juego_crear_juego_sin_posiciones_con_jugadores();

    // AgregarJugador
    static void test_juego_jugadores_con_id_secuencial();

    static void test_juego_jugador_nuevo_no_modifica_expulsados();

    static void test_juego_jugador_nuevo_desconectado();

    static void test_juego_jugador_nuevo_sin_sanciones();

    static void test_juego_jugador_nuevo_sin_pokemones();

    // Conectarse
    static void test_juego_conectarse_jugador_se_conecta();

    static void test_juego_conectarse_jugador_se_agrega_a_posiciones_jugadores();

    static void test_juego_conectarse_jugador_no_en_rango_pokemon_sigue_igual();

    static void test_juego_conectarse_jugador_en_rango_pokemon_se_agrega_al_heap();

    static void test_juego_conectarse_jugador_en_rango_pokemon_se_agrega_it_heap_a_jugadores_por_id();

    static void test_juego_conectarse_jugador_en_rango_pokemon_resetea_contador_pokemon();

    // HayPokemonCercano
    static void test_juego_hay_pokemon_cercano_coordenada_invalida();

    static void test_juego_hay_pokemon_cercano_coordenada_con_pokemon();

    static void test_juego_hay_pokemon_cercano_coordenada_con_pokemon_cercano();

    static void test_juego_hay_pokemon_cercano_coordenada_con_pokemon_lejano();
};


#endif //SRC_TESTSJUEGO_H
