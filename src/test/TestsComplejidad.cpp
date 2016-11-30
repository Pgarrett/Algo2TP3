#include "TestsComplejidad.h"
#include "../mini_test.h"
#include "ctime"
#include "../Driver.h"

using namespace std;

#define TIMED(msg, expr ){\
    clock_t start = clock();\
    (expr);\
    std::cout << msg << " - " << (float(clock() - start ) / CLOCKS_PER_SEC) << std::endl;\
}

#define ANCHO 100
#define LARGO 100
#define STEP 5
#define JUGADORES 600

void TestsComplejidad::correr_tests() {
    RUN_TEST(test_crear_mapa)
    RUN_TEST(test_crear_juego)
    RUN_TEST(test_crear_driver)
    RUN_TEST(test_complejidad)
}

void TestsComplejidad::test_crear_mapa() {
    cout << " " << endl;
    TIMED("crear mapa", crear_mapa());
}

void TestsComplejidad::test_crear_juego() {
    cout << " " << endl;
    const Mapa &mapa = crear_mapa();
    TIMED("copiar mapa", Juego(mapa))
}

void TestsComplejidad::test_crear_driver() {
    cout << " " << endl;
    const Conj<Coordenada> &coordenadas = crear_mapa().coordenadas();
    TIMED("Driver", Driver(coordenadas));
}

void TestsComplejidad::test_complejidad() {
    cout << " " << endl;
    Driver j(crear_mapa().coordenadas());

    TIMED("pokemones", agregarPokemones(j));
    TIMED("jugadores", agregarJugadores(j));
    TIMED("conectar", conectarJugadores(j));
    TIMED("posiciones", posiciones(j));
    for(int i = 0; i < 8; i++)
        moverTodos(j);
    TIMED("mover", moverTodos(j));
}

void TestsComplejidad::moverTodos(Driver& j) {
    Nat n = 0;
    while (n < JUGADORES)
        for (int i = 0; i < LARGO; i += STEP)
            for (int k = 0; k < ANCHO; k += STEP)
                if(n < JUGADORES) {
                    j.moverse(n, j.posicion(n));
                    n++;
                }
}

void TestsComplejidad::posiciones(Driver& j) {
    for (int n = 0; n < JUGADORES; ++n) {
        j.posicion(n);
    }
}

void TestsComplejidad::conectarJugadores(Driver& j) {
    Nat n = 0;
    while (n < JUGADORES)
        for (int i = 0; i < LARGO; i += STEP)
            for (int k = 0; k < ANCHO; k += STEP)
                if(n < JUGADORES)
                    j.conectarse(n++, Coordenada(i, k));
}

Mapa TestsComplejidad::crear_mapa() {
    Mapa m;
    for (int i = 0; i < LARGO; i += STEP) {
        for (int j = 0; j < ANCHO; j += STEP) {
            m.agregarCoordenada(Coordenada(i, j));
        }
    }
    return m;
}

void TestsComplejidad::agregarJugadores(Driver& j) {
    for (int i = 0; i < JUGADORES; ++i) {
        j.agregarJugador();
    }
}

void TestsComplejidad::agregarPokemones(Driver& j) {
    for (int i = 0; i < LARGO; i += STEP) {
        for (int k = 0; k < ANCHO; k += STEP) {
            j.agregarPokemon("poke", Coordenada(i, k));
        }
    }
}
