#ifndef SRC_TESTSMOVERSE_H
#define SRC_TESTSMOVERSE_H

#include "../modulos/Mapa.h"

class TestsMoverse {

public:
    static void correr_tests();

private:

    static void test_moverse_sanciones_iguales_en_movimiento_valido();

    static void test_moverse_sanciones_aumentan_en_movimiento_invalido();

    static void test_moverse_sanciones_expulsar();

    static void test_moverse_no_se_mueve_si_fue_movimiento_invalido();

    static void test_moverse_se_mueve_si_fue_movimiento_valido();

    static void test_moverse_expulsar_cantidad_total_de_pokemones();
//
//
//
//    Atrapar/
//
//    Cantidad de movimientos para captura debería incrementar cuando CASOS
//
//
//            Un pokemon que es atrapado no deberia estar en posConPokemones
//
//            Un pokemon atrapado no deberia estar en un territorio
//
//    Expulsar/
//
//

//
//    La cantidad de pokemones por especie debe bajar cuando se expulsa a alguien con pokemones
//
//            La rareza de un pokemon debe bajar cuando se expulsa a un jugador que lo capturó
//
//            El id del siguiente jugador debe tener en cuenta a los expulsados
//
//            Un jugador expulsado no debe estar entre los conectados
//
//    Un jugador expulsado no debe tener posicion
//
//            Un jugador expulsado no debe ser un entrenador posible


};

#endif //SRC_TESTSMOVERSE_H
