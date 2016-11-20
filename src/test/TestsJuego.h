#ifndef SRC_TESTSJUEGO_H
#define SRC_TESTSJUEGO_H

class TestsJuego {

public:
    static void correr_tests();

private:
    static void test_juego_constructor_con_mapa();

    // Agregar jugador
    static void test_juego_jugadores_con_id_secuencial();

    static void test_juego_jugador_nuevo_desconectado();

    static void test_juego_jugador_nuevo_sin_pokemones();


};


#endif //SRC_TESTSJUEGO_H
