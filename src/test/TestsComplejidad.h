#ifndef SRC_TESTSCOMPLEJIDAD_H
#define SRC_TESTSCOMPLEJIDAD_H


#include "../modulos/Mapa.h"
#include "../modulos/Juego.h"
#include "../Driver.h"

class TestsComplejidad {

public:
    static void correr_tests();

private:
    static void test_crear_mapa();

    static void test_crear_juego();

    static void test_crear_driver();

    static void test_complejidad();

    static Mapa crear_mapa();

    static void agregarPokemones(Driver& j);

    static void agregarJugadores(Driver& j);

    static void conectarJugadores(Driver& j);

    static void posiciones(Driver& j);

    static void moverTodos(Driver& j);
};


#endif //SRC_TESTSCOMPLEJIDAD_H
