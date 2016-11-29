#include "TestsMoverse.h"

#include "../mini_test.h"
#include "../modulos/Juego.h"

typedef Coordenada Coor;
Jugador agregarJugadorConectadoEn(Juego& j, Coor c);
Mapa mapaCon(Coordenada c1, Coordenada c2);
Mapa mapaCon(Coor c1, Coor c2, Coor c3, Coor c4);
Mapa mapaCon(Coor c1, Coor c2, Coor c3, Coor c4, Coor c5);

void TestsMoverse::correr_tests() {
    RUN_TEST(test_moverse_sanciones_iguales_en_movimiento_valido)
    RUN_TEST(test_moverse_sanciones_aumentan_en_movimiento_invalido)
    RUN_TEST(test_moverse_se_mueve_si_fue_movimiento_valido)
    RUN_TEST(test_moverse_no_se_mueve_si_fue_movimiento_invalido)
    RUN_TEST(test_moverse_sanciones_expulsar)
    RUN_TEST(test_moverse_jugador_expulsado_no_esta_en_jugadores)
    RUN_TEST(test_moverse_expulsar_saca_de_entrenadores_posibles)
    RUN_TEST(test_moverse_expulsar_saca_del_mapa_al_jugador)
    RUN_TEST(test_moverse_jugador_expulsado_no_puede_capturar)
//    RUN_TEST(test_moverse_movimientos_captura_en_rango)
//    RUN_TEST(test_moverse_movimientos_captura_sin_entrenadores_cerca)
//    RUN_TEST(test_moverse_movimientos_captura_fuera_de_rango)
//    RUN_TEST(test_moverse_movimientos_captura_movimiento_invalido_no_suma)
//    RUN_TEST(test_moverse_movimientos_captura_en_rango_otro_poke)
//    RUN_TEST(test_moverse_movimientos_captura_sin_entrenadores_cerca_otro_poke)
//    RUN_TEST(test_moverse_movimientos_captura_entro_a_un_rango)
//    RUN_TEST(test_moverse_movimientos_captura_sale_de_un_rango)
//    RUN_TEST(test_moverse_expulsar_cantidad_total_de_pokemones)
}

//    Las sanciones deben mantenerse iguales si se movió de forma valida
void TestsMoverse::test_moverse_sanciones_iguales_en_movimiento_valido() {
    Coordenada c1(1, 1), c2(1, 2);
    Juego juego(mapaCon(c1, c2));
    Jugador j = juego.agregarJugador();

    juego.conectarse(j, c1);
    juego.moverse(j, c2);

    ASSERT_EQ(juego.sanciones(j), 0)
}

Mapa mapaCon(Coordenada c1, Coordenada c2) {
    Mapa mapa;
    mapa.agregarCoordenada(c1);
    mapa.agregarCoordenada(c2);
    return mapa;
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

//    Las sanciones deben incrementar en 1 si se movió de forma invalida
void TestsMoverse::test_moverse_sanciones_aumentan_en_movimiento_invalido() {
    Coordenada c1(1, 1), c3(3, 3);
    Juego juego(mapaCon(c1, c3));
    Jugador j = juego.agregarJugador();

    juego.conectarse(j, c1);
    juego.moverse(j, c3);

    ASSERT_EQ(juego.sanciones(j), 1)
}

//    Un jugador con 4 sanciones debe ser expulsado al moverse de forma invalida
void TestsMoverse::test_moverse_sanciones_expulsar() {
    Coordenada c1(1, 1), c3(3, 3);
    Juego juego(mapaCon(c1, c3));
    Jugador j = agregarJugadorConectadoEn(juego, c1);

    for (int i = 0; i < 4; i++)
        juego.moverse(j, c3);


    ASSERT_EQ(juego.sanciones(j), 4)
    ASSERT(juego.expulsados().EsVacio());

    juego.moverse(j, c3); // 5 sanciones

    ASSERT(not juego.expulsados().EsVacio());
    ASSERT(juego.expulsados().Pertenece(j));
}

Jugador agregarJugadorConectadoEn(Juego& j, Coor c){
    Jugador jugador = j.agregarJugador();
    j.conectarse(jugador, c);
    return jugador;
}

//    Un jugador que es expulsado no deberia estar en jugadores
void TestsMoverse::test_moverse_jugador_expulsado_no_esta_en_jugadores() {
    Coordenada c1(1, 1), c3(3, 3);
    Juego juego(mapaCon(c1, c3));
    Jugador j = agregarJugadorConectadoEn(juego, c1);

    for (int i = 0; i < 5; i++)
        juego.moverse(j, c3);

    ASSERT(not juego.jugadores().Pertenece(j));
}

//  el jugador debe seguir en el mismo lugar si se movió de forma invalida
// (esto es lo que estaba en el mail, habria que consultarlo)
void TestsMoverse::test_moverse_no_se_mueve_si_fue_movimiento_invalido() {
    Coordenada c1(1, 1), c3(3, 3);
    Juego juego(mapaCon(c1, c3));
    Jugador j = agregarJugadorConectadoEn(juego, c1);

    juego.moverse(j, c3); // movimiento invalido

    ASSERT(juego.posicion(j) == c1)
}

// Un jugador expulsado no debe ser un entrenador posible
void TestsMoverse::test_moverse_expulsar_saca_de_entrenadores_posibles() {
    Coordenada c1(1, 1), c3(3, 3);
    Juego juego(mapaCon(c1, c3));
    Jugador j1 = agregarJugadorConectadoEn(juego, c1);
    juego.agregarPokemon("poke", c1);

    //expulsar
    for(int i = 0; i < 5; i++)
        juego.moverse(j1, c3);

    ASSERT(juego.entrenadoresPosibles(c1).EsVacio())
}

// Un jugador expulsado no debe seguir en su posicion
void TestsMoverse::test_moverse_expulsar_saca_del_mapa_al_jugador() {
    Coordenada c1(1, 1), c3(3, 3);
    Juego juego(mapaCon(c1, c3));
    Jugador j1 = agregarJugadorConectadoEn(juego, c1);

    //expulsar
    for(int i = 0; i < 5; i++)
        juego.moverse(j1, c3);

    ASSERT(not juego.jugadoresEnPos(c1).HaySiguiente())
}

void TestsMoverse::test_moverse_jugador_expulsado_no_puede_capturar() {
    Coordenada c1(1, 1), c2(1, 2), c3(4, 4), c4(4, 5);
    Mapa mapa = mapaCon(c1, c2, c3, c4);
    Juego juego(mapa);
    Jugador j1 = agregarJugadorConectadoEn(juego, c1);
    Jugador j2 = agregarJugadorConectadoEn(juego, c3);
    juego.agregarPokemon("poke", c2);

    // Expulsar a j1
    for(int i = 0; i < 5; i++)
        juego.moverse(j1, c3);

    // j2 se mueve 10 veces
    for (int i = 0; i < 5; ++i) {
        juego.moverse(j2, c4);
        juego.moverse(j2, c3);
    }

    // el pokemon sigue libre como el sol cuando amanece, como el mar
    ASSERT(juego.hayPokemonCercano(c2))
    ASSERT_EQ(juego.pokemonEnPos(c2), "poke")
}

Mapa mapaCon(Coor c1, Coor c2, Coor c3, Coor c4) {
    Mapa m = mapaCon(c1, c2);
    m.agregarCoordenada(c3);
    m.agregarCoordenada(c4);
    return m;
}

//    La cantidad de pokemones totales debe bajar cuando se expulsa a alguien con pokemones
void TestsMoverse::test_moverse_expulsar_cantidad_total_de_pokemones() {
    Coordenada c1(1, 1), c2(1, 2), c3(4, 4), c4(4, 5);
    Mapa mapa = mapaCon(c1, c2, c3, c4);
    Juego juego(mapa);
    Jugador j1 = agregarJugadorConectadoEn(juego, c1);
    Jugador j2 = agregarJugadorConectadoEn(juego, c3);
    juego.agregarPokemon("poke", c2);

    for (int i = 0; i < 5; ++i) {
        juego.moverse(j2, c4);
        juego.moverse(j2, c3);
    }
    // j1 atrapo pokemon
    ASSERT(juego.cantPokemonsTotales() == 1)

    // Expulsar
    for(int i = 0; i < 5; i++)
        juego.moverse(j1, c3);
    ASSERT(juego.cantPokemonsTotales() == 0)
}

// El contador de un pokemon no deberia aumentar si el jugador se movio en el rango
void TestsMoverse::test_moverse_movimientos_captura_en_rango() {
    Coordenada c1(1, 1), c2(1, 2);
    Juego juego(mapaCon(c1, c2));
    Jugador j = agregarJugadorConectadoEn(juego, c1);
    juego.agregarPokemon("poke", c1);

    juego.moverse(j, c2);

    ASSERT_EQ(juego.cantMovimientosParaCaptura(c1), 10)
}

void TestsMoverse::test_moverse_movimientos_captura_sin_entrenadores_cerca() {
    Coordenada c1(1, 1), c2(1, 2), c3(5, 5), c4(5, 6);
    Juego juego(mapaCon(c1, c2, c3, c4));
    Jugador j = agregarJugadorConectadoEn(juego, c1);
    juego.agregarPokemon("poke", c4);

    juego.moverse(j, c2);
    juego.moverse(j, c1);
    juego.moverse(j, c2);

    ASSERT_EQ(juego.cantMovimientosParaCaptura(c4), 0)
}

void TestsMoverse::test_moverse_movimientos_captura_fuera_de_rango() {
    Coordenada c1(1, 1), c2(1, 2), c3(5, 5), c4(5, 6);
    Juego juego(mapaCon(c1, c2, c3, c4));
    Jugador j = agregarJugadorConectadoEn(juego, c1);
    juego.agregarPokemon("poke", c4);
    agregarJugadorConectadoEn(juego, c4);

    juego.moverse(j, c2);
    juego.moverse(j, c1);

    ASSERT_EQ(juego.cantMovimientosParaCaptura(c4), 8)
}

void TestsMoverse::test_moverse_movimientos_captura_movimiento_invalido_no_suma() {
    Coordenada c1(1, 1), c2(9, 9), c3(5, 5), c4(5, 6);
    Juego juego(mapaCon(c1, c2, c3, c4));
    Jugador j = agregarJugadorConectadoEn(juego, c1);
    juego.agregarPokemon("poke", c4);
    agregarJugadorConectadoEn(juego, c4);

    juego.moverse(j, c2); // Movimiento invalido
    juego.moverse(j, c2); // Movimiento invalido
    juego.moverse(j, c2); // Movimiento invalido

    ASSERT_EQ(juego.cantMovimientosParaCaptura(c4), 10)
}

// El contador de un pokemon deberia aumentar si un jugador se movio en el rango de otro pokemon
void TestsMoverse::test_moverse_movimientos_captura_en_rango_otro_poke() {
    Coordenada c1(1, 1), c2(1, 2), c3(9, 9), c4(9, 10);
    Juego juego(mapaCon(c1, c2, c3, c4));
    Jugador j = agregarJugadorConectadoEn(juego, c1);
    juego.agregarPokemon("poke", c1);
    agregarJugadorConectadoEn(juego, c3);
    juego.agregarPokemon("poke2", c4);

    juego.moverse(j, c2);
    juego.moverse(j, c1);

    ASSERT_EQ(juego.cantMovimientosParaCaptura(c4), 8)
    ASSERT_EQ(juego.cantMovimientosParaCaptura(c1), 10)
}

// El contador de un pokemon sin jugadores cerca no deberia aumentar si un jugador se movio en el rango de otro pokemon
void TestsMoverse::test_moverse_movimientos_captura_sin_entrenadores_cerca_otro_poke(){
    Coordenada c1(1, 1), c2(1, 2), c3(9, 9), c4(9, 10);
    Juego juego(mapaCon(c1, c2, c3, c4));
    Jugador j = agregarJugadorConectadoEn(juego, c1);
    juego.agregarPokemon("poke", c1);
    juego.agregarPokemon("poke2", c4);

    juego.moverse(j, c2);
    juego.moverse(j, c1);

    ASSERT_EQ(juego.cantMovimientosParaCaptura(c4), 0)
    ASSERT_EQ(juego.cantMovimientosParaCaptura(c1), 10)
}

// el contador de un pokemon deberia resetearse cuando un entrenador entra al rango
void TestsMoverse::test_moverse_movimientos_captura_entro_a_un_rango() {
    Coordenada c1(1, 1), c2(1, 2), c3(1, 3), c4(1, 4), c5(1, 5);
    Juego juego(mapaCon(c1, c2, c3, c4, c5));
    agregarJugadorConectadoEn(juego, c5);
    juego.agregarPokemon("poke2", c5);
    Jugador j = agregarJugadorConectadoEn(juego, c1);
    
    juego.moverse(j, c2); // se acerca al rango sin entrar
    ASSERT(not juego.hayPokemonCercano(c2))
    ASSERT_EQ(juego.cantMovimientosParaCaptura(c5), 9)

    juego.moverse(j, c3); // entra al rango
    ASSERT(juego.hayPokemonCercano(c3))
    ASSERT_EQ(juego.cantMovimientosParaCaptura(c5), 10)
}

Mapa mapaCon(Coor c1, Coor c2, Coor c3, Coor c4, Coor c5){
    Mapa m = mapaCon(c1, c2, c3, c4);
    m.agregarCoordenada(c5);
    return m;
}

// El contador de un pokemon deberia aumentar cuando un entrenador sale del rango
void TestsMoverse::test_moverse_movimientos_captura_sale_de_un_rango() {
    Coordenada c1(1, 1), c2(1, 2), c3(1, 3), c4(1, 4), c5(1, 5);
    Juego juego(mapaCon(c1, c2, c3, c4, c5));
    agregarJugadorConectadoEn(juego, c5);
    juego.agregarPokemon("poke2", c5);
    Jugador j = agregarJugadorConectadoEn(juego, c5);

    juego.moverse(j, c3); // se mueve al borde del rango sin salir
    ASSERT(juego.hayPokemonCercano(c3))
    ASSERT_EQ(juego.cantMovimientosParaCaptura(c5), 10)

    juego.moverse(j, c2); // sale del rango
    ASSERT(not juego.hayPokemonCercano(c2))
    ASSERT_EQ(juego.cantMovimientosParaCaptura(c5), 9)
}