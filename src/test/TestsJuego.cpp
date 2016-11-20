#include "TestsJuego.h"
#include "../mini_test.h"
#include "../modulos/Juego.h"

typedef Coordenada Coor;

void TestsJuego::correr_tests() {
    RUN_TEST(test_juego_constructor_con_mapa);
//    RUN_TEST(test_agregar_jugadores);
//    RUN_TEST(test_agregar_pokemones);
}

void TestsJuego::test_juego_constructor_con_mapa() {
    Mapa mapa;
    mapa.agregarCoordenada(Coor(0, 0));
    mapa.agregarCoordenada(Coor(0, 1));
    mapa.agregarCoordenada(Coor(0, 2));
    mapa.agregarCoordenada(Coor(1, 2));
    mapa.agregarCoordenada(Coor(10, 0));
    mapa.agregarCoordenada(Coor(1, 4));

    Juego j(mapa);

    ASSERT(j.mapa().coordenadas() == mapa.coordenadas());
}

void TestsJuego::test_juego_jugadores_con_id_secuencial() {

}




