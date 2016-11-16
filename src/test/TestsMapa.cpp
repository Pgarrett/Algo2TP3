#include "TestsMapa.h"

#include "../mini_test.h"
#include "../modulos/Mapa.h"

void TestsMapa::correr_tests() {
    RUN_TEST(test_mapa_crear)
    RUN_TEST(test_mapa_agregar_coordenada)
    RUN_TEST(test_mapa_coordenadas_repetidas)
    RUN_TEST(test_mapa_coordenadas)
    RUN_TEST(test_mapa_pos_existente)
    RUN_TEST(test_mapa_pos_inexistente)
//    RUN_TEST(test_mapa_ancho_sin_coords)
    RUN_TEST(test_mapa_ancho)
    RUN_TEST(test_mapa_largo)
    RUN_TEST(test_mapa_no_hay_camino)
    RUN_TEST(test_mapa_hay_camino)
    RUN_TEST(test_mapa_hay_camino_largo)
}


// El mapa deberia crearse sin coordenadas
void TestsMapa::test_mapa_crear() {
    Mapa mapa;

    ASSERT(mapa.coordenadas().EsVacio());
}


// El mapa deberia tener coordenadas cuando se le agregan
void TestsMapa::test_mapa_agregar_coordenada() {
    Mapa mapa;

    mapa.agregarCoordenada(Coordenada(1, 1));

    ASSERT(!mapa.coordenadas().EsVacio())
}


// El mapa no deberia tener coordenadas repetidas
void TestsMapa::test_mapa_coordenadas_repetidas() {
    Mapa mapa;

    mapa.agregarCoordenada(Coordenada(1, 1));
    mapa.agregarCoordenada(Coordenada(1, 1));

    ASSERT_EQ(1, mapa.coordenadas().Cardinal())
}

static Mapa crear_mapa_con(Coordenada c1, Coordenada c2, Coordenada c3) {
    Mapa mapa;
    mapa.agregarCoordenada(c1);
    mapa.agregarCoordenada(c2);
    mapa.agregarCoordenada(c3);
    return mapa;
}

// El mapa deberia devolver solo las coordenadas que se le agregaron
void TestsMapa::test_mapa_coordenadas() {
    Coordenada c1(1, 1), c2(2, 2), c3(3, 3);
    Mapa mapa = crear_mapa_con(c1, c2, c3);

    Conj<Coordenada> coordenadas = mapa.coordenadas();

    ASSERT(coordenadas.Pertenece(c1));
    ASSERT(coordenadas.Pertenece(c2));
    ASSERT(coordenadas.Pertenece(c3));
    ASSERT_EQ(mapa.coordenadas().Cardinal(), 3);
}


// Una coordenada sin agregar no deberia existir en el mapa
void TestsMapa::test_mapa_pos_inexistente() {
    Mapa mapa;

    ASSERT(!mapa.posExistente(Coordenada(2, 2)));
}


// Una coordenada agregada deberia existir en el mapa
void TestsMapa::test_mapa_pos_existente() {
    Mapa mapa;
    Coordenada coor(1, 1);

    mapa.agregarCoordenada(coor);

    ASSERT(mapa.posExistente(coor));
}

// Pedir el ancho de un mapa sin coordenadas deberia tirar error por restricciones
void TestsMapa::test_mapa_ancho_sin_coords() {
    Mapa mapa;
    bool error;

    try {
        mapa.ancho();
    } catch (...) {
        error = true;
    }

    ASSERT(error);
}


// El ancho del mapa deberia ser uno mas que la latitud mas grande entre las coordenadas
void TestsMapa::test_mapa_ancho() {
    Coordenada c1(1, 4), c2(2, 2), c3(8, 3);
    Mapa mapa = crear_mapa_con(c1, c2, c3);

    Nat ancho = mapa.ancho();

    ASSERT_EQ(ancho, 5);
}

// El largo del mapa deberia ser uno mas que la latitud mas grande entre las coordenadas
void TestsMapa::test_mapa_largo() {
    Coordenada c1(1, 8), c2(2, 2), c3(5, 3);
    Mapa mapa = crear_mapa_con(c1, c2, c3);

    Nat largo = mapa.largo();

    ASSERT_EQ(largo, 6);
}

// No deberia haber un camino entre dos coordenadas no conexas
void TestsMapa::test_mapa_no_hay_camino() {
    Coordenada c1(1, 2), c2(3, 3), c3(4, 4);

    Mapa mapa = crear_mapa_con(c1, c2, c3);

    ASSERT(!mapa.hayCamino(c1, c3))
    ASSERT(!mapa.hayCamino(c2, c3))
}

// Deberia haber camino entre coordenadas juntas
void TestsMapa::test_mapa_hay_camino() {
    Mapa mapa;
    Coordenada c1(1, 1), c2(1, 2);

    mapa.agregarCoordenada(c1);
    mapa.agregarCoordenada(c2);

    ASSERT(mapa.hayCamino(c1, c2))
}

// Deberia haber camino entre coordenadas unidas por otras coordenadas
void TestsMapa::test_mapa_hay_camino_largo() {
    Coordenada c1(1, 1), c2(1, 2), c3(2, 2);

    Mapa mapa = crear_mapa_con(c1, c2, c3);

    ASSERT(mapa.hayCamino(c1, c3))
    ASSERT(mapa.hayCamino(c3, c1))
}