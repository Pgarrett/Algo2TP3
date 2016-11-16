#ifndef SRC_TESTSDICCMAT_H
#define SRC_TESTSDICCMAT_H

class TestsDiccMat {

public:
    static void correr_tests();

private:
    static void test_diccmat_crear();

    static void test_diccmat_ancho();

    static void test_diccmat_largo();

    static void test_diccmat_definido();

    static void test_diccmat_definir();

    static void test_diccmat_redefinir();

    static void test_diccmat_coordenadas();

    static void test_diccmat_coordenadas_sin_repetir();

    static void test_diccmat_significado();

    static void test_diccmat_significado_redefinido();

    static void test_diccmat_borrar();

    static void test_diccmat_coordenadas_borradas();

    static void test_diccmat_borrar_y_definir();

    static void test_diccmat_general();

    static void test_diccmat_no_cuadrada();
};


#endif //SRC_TESTSDICCMAT_H
