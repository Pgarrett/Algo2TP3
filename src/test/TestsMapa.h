#ifndef SRC_TESTSMAPA_H
#define SRC_TESTSMAPA_H

class TestsMapa {

public:
    static void correr_tests();

private:
    static void test_crear_mapa();

    static void test_agregar_coordenada();

    static void test_coordenadas_repetidas();

    static void test_coordenadas();

    static void test_pos_existente();

    static void test_pos_inexistente();

    static void test_hay_camino();

    static void ancho();

    static void largo();
};


#endif //SRC_TESTSMAPA_H
