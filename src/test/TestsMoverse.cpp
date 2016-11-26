#include "TestsMoverse.h"

#include "../mini_test.h"
#include "../modulos/Juego.h"

typedef Coordenada Coor;

void TestsMoverse::correr_tests() {
    RUN_TEST(test_moverse_sanciones_iguales_en_movimiento_valido)
    RUN_TEST(test_moverse_sanciones_aumentan_en_movimiento_invalido)
    RUN_TEST(test_moverse_sanciones_expulsar)
    RUN_TEST(test_moverse_no_se_mueve_si_fue_movimiento_invalido)
    RUN_TEST(test_moverse_se_mueve_si_fue_movimiento_valido)
    RUN_TEST(test_moverse_expulsar_cantidad_total_de_pokemones)
}

Mapa mapaCon(Coordenada c1, Coordenada c2);

//    Las sanciones deben mantenerse iguales si se movió de forma valida
void TestsMoverse::test_moverse_sanciones_iguales_en_movimiento_valido() {
    Coordenada c1(1, 1), c2(1, 2);
    Juego juego(mapaCon(c1, c2));
    Jugador j = juego.agregarJugador();

    juego.conectarse(j, c1);
    juego.moverse(j, c2);

    ASSERT(juego.sanciones(j) == 0)
}

Mapa mapaCon(Coordenada c1, Coordenada c2) {
    Mapa mapa;
    mapa.agregarCoordenada(c1);
    mapa.agregarCoordenada(c2);
    return mapa;
}

//    Las sanciones deben incrementar en 1 si se movió de forma invalida
void TestsMoverse::test_moverse_sanciones_aumentan_en_movimiento_invalido() {
    Coordenada c1(1, 1), c3(3, 3);
    Juego juego(mapaCon(c1, c3));
    Jugador j = juego.agregarJugador();

    juego.conectarse(j, c1);
    juego.moverse(j, c3);

    ASSERT(juego.sanciones(j) == 1)
}

//    Un jugador con 4 sanciones debe ser expulsado al moverse de forma invalida
void TestsMoverse::test_moverse_sanciones_expulsar() {
    Coordenada c1(1, 1), c3(3, 3);
    Juego juego(mapaCon(c1, c3));
    Jugador j = juego.agregarJugador();

    juego.conectarse(j, c1);
    juego.moverse(j, c3); // 1 sancion
    juego.moverse(j, c1); // 2 sanciones
    juego.moverse(j, c3); // 3 sanciones
    juego.moverse(j, c1); // 4 sanciones


    ASSERT(juego.sanciones(j) == 4)
    ASSERT(juego.expulsados().EsVacio());

    juego.moverse(j, c3); // 5 sanciones

    ASSERT(not juego.expulsados().EsVacio());
    ASSERT(juego.expulsados().Pertenece(j));
}


//  el jugador debe seguir en el mismo lugar si se movió de forma invalida
// (esto es lo que estaba en el mail, habria que consultarlo)
void TestsMoverse::test_moverse_no_se_mueve_si_fue_movimiento_invalido() {
    Coordenada c1(1, 1), c3(3, 3);
    Juego juego(mapaCon(c1, c3));
    Jugador j = juego.agregarJugador();

    juego.conectarse(j, c1);
    juego.moverse(j, c3); // movimiento invalido

    ASSERT(juego.posicion(j) == c1)
}

//    Debe moverse si se movió de forma válida
void TestsMoverse::test_moverse_se_mueve_si_fue_movimiento_valido() {
    Coordenada c1(1, 1), c2(1, 2);
    Juego juego(mapaCon(c1, c2));
    Jugador j = juego.agregarJugador();

    juego.conectarse(j, c1);
    juego.moverse(j, c2); // movimiento valido

    ASSERT(juego.posicion(j) == c2)
}

//    La cantidad de pokemones totales debe bajar cuando se expulsa a alguien con pokemones
void TestsMoverse::test_moverse_expulsar_cantidad_total_de_pokemones() {
    Coordenada c1(1, 1), c2(1, 2), c3(4, 4), c4(4, 5);
    Mapa mapa = mapaCon(c1, c2);
    mapa.agregarCoordenada(c3);
    mapa.agregarCoordenada(c4);

    Juego juego(mapa);

    Jugador j1 = juego.agregarJugador();
    Jugador j2 = juego.agregarJugador();

    juego.agregarPokemon("poke", c2);

    juego.conectarse(j1, c1);
    juego.conectarse(j2, c3);

    for (int i = 0; i < 5; ++i) {
        juego.moverse(j2, c4);
        juego.moverse(j2, c3);
    }

    // j1 atrapo pokemon
    ASSERT(juego.cantPokemonsTotales() == 1)

    juego.moverse(j1, c3);
    juego.moverse(j1, c1);
    juego.moverse(j1, c3);
    juego.moverse(j1, c1);
    juego.moverse(j1, c3);

    // expulsado
    ASSERT(juego.cantPokemonsTotales() == 0)
}




