#include "TestsDiccMat.h"
#include "../mini_test.h"
#include "../modulos/DiccMat.h"

typedef Coordenada Coor;

void TestsDiccMat::correr_tests() {
    RUN_TEST(test_diccmat_crear)
    RUN_TEST(test_diccmat_ancho)
    RUN_TEST(test_diccmat_largo)
    RUN_TEST(test_diccmat_definido)
    RUN_TEST(test_diccmat_definir)
//    RUN_TEST(test_diccmat_coordenadas)
}


// El diccmat no deberia iniciarse con valores definidos
void TestsDiccMat::test_diccmat_crear() {
    DiccMat<Nat> d(1, 1);

    ASSERT(!d.coordenadas().HaySiguiente())
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

// El diccmat deberia devolver un iterador a todas las coordenadas con valores
void TestsDiccMat::test_diccmat_coordenadas() {
    DiccMat<Nat> d(2, 2);
}


