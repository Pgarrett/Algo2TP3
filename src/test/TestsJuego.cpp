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

//    RUN_TEST(test_agregar_jugadores);
//    RUN_TEST(test_agregar_pokemones);
}

void TestsJuego::test_juego_constructor_con_mapa() {
    Mapa mapa = crearMapaDefault();

    Juego j(mapa);

    ASSERT(j.mapa().coordenadas() == mapa.coordenadas());
}

Mapa crearMapaDefault(){
    Mapa mapa;
    mapa.agregarCoordenada(Coor(0, 0));
    mapa.agregarCoordenada(Coor(0, 1));
    mapa.agregarCoordenada(Coor(0, 2));
    mapa.agregarCoordenada(Coor(1, 2));
    mapa.agregarCoordenada(Coor(10, 0));
    mapa.agregarCoordenada(Coor(1, 4));
    return mapa;
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
    Mapa mapa = crearMapaDefault();
    Juego j(mapa);

    Jugador jug = j.agregarJugador();

    ASSERT(j.sanciones(jug) == 0);
}


