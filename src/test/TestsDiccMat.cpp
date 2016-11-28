#include "TestsDiccMat.h"
#include "../mini_test.h"
#include "../modulos/DiccMat.h"

typedef Coordenada Coor;
typedef Conj<Coordenada>::const_Iterador ItConj;

void TestsDiccMat::correr_tests() {
    RUN_TEST(test_diccmat_crear)
    RUN_TEST(test_diccmat_ancho)
    RUN_TEST(test_diccmat_largo)
    RUN_TEST(test_diccmat_definido)
    RUN_TEST(test_diccmat_definir)
    RUN_TEST(test_diccmat_redefinir)
    RUN_TEST(test_diccmat_coordenadas)
    RUN_TEST(test_diccmat_coordenadas_sin_repetir)
    RUN_TEST(test_diccmat_significado)
    RUN_TEST(test_diccmat_significado_redefinido)
    RUN_TEST(test_diccmat_borrar)
    RUN_TEST(test_diccmat_coordenadas_borradas)
    RUN_TEST(test_diccmat_borrar_y_definir)
    RUN_TEST(test_diccmat_general)
    RUN_TEST(test_diccmat_no_cuadrada)
}


// El diccmat no deberia iniciarse con valores definidos
void TestsDiccMat::test_diccmat_crear() {
    DiccMat<Nat> d(1, 1);

    ASSERT(d.coordenadas().EsVacio())
}


// Pedirle el ancho al diccmat deberia devolver el que se le paso al crearlo
void TestsDiccMat::test_diccmat_ancho() {
    DiccMat<Nat> d(1, 5);

    ASSERT_EQ(d.ancho(), 5);
}


// Pedirle el largo al diccmat deberia devolver el que se le paso al crearlo
void TestsDiccMat::test_diccmat_largo() {
    DiccMat<Nat> d(1, 5);

    ASSERT_EQ(d.largo(), 1);
}


// Una coordenada sin un valor definido no deberia estar definida
void TestsDiccMat::test_diccmat_definido() {
    DiccMat<Nat> d(1, 1);

    bool definido = d.definido(Coor(0, 0));

    ASSERT(!definido)
}

// Una coordenada definida deberia estar definida
void TestsDiccMat::test_diccmat_definir() {
    DiccMat<Nat> d(1, 1);
    Coordenada c(0, 0);

    d.definir(c, 31415);

    ASSERT(d.definido(c))
}


// Una coordenada redefinida deberia seguir estando definida
void TestsDiccMat::test_diccmat_redefinir() {
    DiccMat<Nat> d(1, 1);
    Coordenada c(0, 0);

    d.definir(c, 31415);
    d.definir(c, 27182);

    ASSERT(d.definido(c))
}

Coor siguiente(ItConj &it) {
    ASSERT(it.HaySiguiente());
    Coor c = it.Siguiente();
    it.Avanzar();
    return c;
}

// El diccmat deberia devolver un iterador a todas las coordenadas con valores
void TestsDiccMat::test_diccmat_coordenadas() {
    DiccMat<Nat> d(2, 2);
    Coor c1(1, 1), c2(0, 1);

    d.definir(c1, 1);
    d.definir(c2, 2);

    Conj<Coordenada> cs = d.coordenadas();
    ItConj it = cs.CrearIt();

    Coor clave1 = siguiente(it);
    Coor clave2 = siguiente(it);
    ASSERT(!it.HaySiguiente());
    ASSERT(clave1 != clave2);
    ASSERT(clave1 == c1 || clave1 == c2);
    ASSERT(clave2 == c1 || clave2 == c2);
}


// Las coordenadas no deberian tener repetidos
void TestsDiccMat::test_diccmat_coordenadas_sin_repetir() {
    DiccMat<Nat> d(2, 2);
    Coor c1(1, 1);

    d.definir(c1, 1);
    d.definir(c1, 100);

    Conj<Coordenada> cs = d.coordenadas();
    ItConj it = cs.CrearIt();

    Coor clave = siguiente(it);
    ASSERT(!it.HaySiguiente());
    ASSERT(clave == c1);
}


// Significado deberia devolver el valor definido para una coordenada
void TestsDiccMat::test_diccmat_significado() {
    DiccMat<Nat> d(2, 2);
    Coor c(1, 1);

    d.definir(c, 10);

    ASSERT_EQ(d.significado(c), 10)
}


// Significado deberia devolver el ultimoo valor definido para una coordenada redefinida
void TestsDiccMat::test_diccmat_significado_redefinido() {
    DiccMat<Nat> d(2, 2);
    Coor c(1, 1);

    d.definir(c, 1);
    d.definir(c, 20);

    ASSERT_EQ(d.significado(c), 20)
}

// Un valor borrado no deberia estar definido
void TestsDiccMat::test_diccmat_borrar() {
    DiccMat<Nat> d(2, 2);
    Coor c(1, 1);
    d.definir(c, 1);

    d.borrar(c);

    ASSERT(!d.definido(c))
}


// Un valor borrado no deberia estar en las coordenadas
void TestsDiccMat::test_diccmat_coordenadas_borradas() {
    DiccMat<Nat> d(2, 2);
    Coor c_borrada(1, 1), c_definida(0, 0);
    d.definir(c_borrada, 1);
    d.definir(c_definida, 2);

    d.borrar(c_borrada);

    Conj<Coordenada> cs = d.coordenadas();
    ItConj it = cs.CrearIt();

    Coor coordenada = siguiente(it);
    ASSERT(!it.HaySiguiente());
    ASSERT(coordenada == c_definida);
}


// Un valor borrado y definido devuelta deberia tener el valor nuevo
void TestsDiccMat::test_diccmat_borrar_y_definir() {
    DiccMat<Nat> d(2, 2);
    Coor c(1, 1);
    d.definir(c, 1);

    d.borrar(c);
    d.definir(c, 10);

    ASSERT(d.definido(c))
    ASSERT_EQ(d.significado(c), 10);
}


// Varias operaciones, para valgrind
void TestsDiccMat::test_diccmat_general() {
    DiccMat<Nat> d(20, 20);

    // Definir
    d.definir(Coor(0, 0), 1);
    d.definir(Coor(3, 1), 1);
    d.definir(Coor(0, 2), 1);
    d.definir(Coor(2, 3), 1);
    d.definir(Coor(0, 4), 1);
    d.definir(Coor(1, 5), 1);
    d.definir(Coor(19, 19), 10);
    d.definir(Coor(5, 1), 1);
    d.definir(Coor(3, 2), 1);
    d.definir(Coor(11, 3), 1);
    d.definir(Coor(10, 14), 1);
    d.definir(Coor(17, 15), 1);

    // Redefinir
    d.definir(Coor(0, 2), 3);
    d.definir(Coor(0, 0), 5);
    d.definir(Coor(2, 3), 1);
    d.definir(Coor(5, 1), 4);
    d.definir(Coor(3, 2), 2);
    d.definir(Coor(11, 3), 15);

    //Borrar
    d.borrar(Coor(2, 3));
    d.borrar(Coor(3, 2));
    d.borrar(Coor(1, 5));
    d.borrar(Coor(5, 1));
    d.borrar(Coor(10, 14));

    // Redefinir en borradas
    d.definir(Coor(2, 3), 1);
    d.definir(Coor(5, 1), 4);
    d.definir(Coor(10, 14), 15);

    // Definido?
    ASSERT(d.definido(Coor(0, 0)))
    ASSERT(d.definido(Coor(3, 1)))
    ASSERT(d.definido(Coor(0, 2)))
    ASSERT(d.definido(Coor(2, 3)))
    ASSERT(d.definido(Coor(0, 4)))
    ASSERT(d.definido(Coor(19, 19)))
    ASSERT(d.definido(Coor(5, 1)))
    ASSERT(d.definido(Coor(11, 3)))
    ASSERT(d.definido(Coor(10, 14)))
    ASSERT(d.definido(Coor(17, 15)))

    // Significado
    ASSERT_EQ(d.significado(Coor(0, 0)), 5)
    ASSERT_EQ(d.significado(Coor(3, 1)), 1)
    ASSERT_EQ(d.significado(Coor(2, 3)), 1)
    ASSERT_EQ(d.significado(Coor(0, 4)), 1)
    ASSERT_EQ(d.significado(Coor(19, 19)), 10)
    ASSERT_EQ(d.significado(Coor(5, 1)), 4)
    ASSERT_EQ(d.significado(Coor(11, 3)), 15)
    ASSERT_EQ(d.significado(Coor(10, 14)), 15)
    ASSERT_EQ(d.significado(Coor(17, 15)), 1)
}

// Caso que daba error al aplanar
void TestsDiccMat::test_diccmat_no_cuadrada() {
    DiccMat<Nat> d(4, 3);
    Coor c1(3, 0), c2(0, 1);

    d.definir(c1, 4);
    d.definir(c2, 8);

    ASSERT_EQ( d.significado(c1), 4)
    ASSERT_EQ( d.significado(c2), 8)
}