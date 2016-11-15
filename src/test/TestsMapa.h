#ifndef SRC_TESTSMAPA_H
#define SRC_TESTSMAPA_H

class TestsMapa {

public:
    static void correr_tests();

private:
    static void test_mapa_crear();

    static void test_mapa_agregar_coordenada();

    static void test_mapa_coordenadas_repetidas();

    static void test_mapa_coordenadas();

    static void test_mapa_pos_existente();

    static void test_mapa_pos_inexistente();

    static void test_mapa_ancho_sin_coords(); // TODO ver como testear restricciones

    static void test_mapa_ancho();

    static void test_mapa_largo();

    static void test_mapa_hay_camino();

    static void test_mapa_copia();
};


#endif //SRC_TESTSMAPA_H
