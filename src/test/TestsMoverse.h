#ifndef SRC_TESTSMOVERSE_H
#define SRC_TESTSMOVERSE_H

#include "../modulos/Mapa.h"

class TestsMoverse {

public:
    static void correr_tests();

private:

    static void test_moverse_sanciones_iguales_en_movimiento_valido();

    static void test_moverse_sanciones_aumentan_en_movimiento_invalido();

    static void test_moverse_se_mueve_si_fue_movimiento_valido();

    static void test_moverse_no_se_mueve_si_fue_movimiento_invalido();

    static void test_moverse_sanciones_expulsar();

    static void test_moverse_jugador_expulsado_no_esta_en_jugadores();

    static void test_moverse_expulsar_saca_de_entrenadores_posibles();

    static void test_moverse_expulsar_saca_del_mapa_al_jugador();

    static void test_moverse_jugador_expulsado_no_puede_capturar();

    static void test_moverse_movimientos_captura_en_rango();

    static void test_moverse_movimientos_captura_sin_entrenadores_cerca();

    static void test_moverse_movimientos_captura_fuera_de_rango();

    static void test_moverse_movimientos_captura_movimiento_invalido_no_suma();

    static void test_moverse_movimientos_captura_en_rango_otro_poke();

    static void test_moverse_movimientos_captura_sin_entrenadores_cerca_otro_poke();

    static void test_moverse_movimientos_captura_entro_a_un_rango();

    static void test_moverse_movimientos_captura_sale_de_un_rango();

    static void test_moverse_movimientos_captura_conectarse_fuera_del_rango();

    static void test_moverse_movimientos_captura_conectarse_en_el_rango();

    static void test_moverse_movimientos_captura_no_aumentan_con_desconectado();

    static void test_moverse_movimientos_captura_no_aumentan_con_expulsado();

    static void test_moverse_atrapar_a_los_10_movimientos();

    static void test_moverse_pokemon_atrapado_no_tiene_posicion();

    static void test_moverse_atrapa_el_jugador_con_menos_pokemones();

    static void test_moverse_si_salio_del_rango_no_atrapa();

    static void test_moverse_jugador_desconectado_no_atrapa();

    static void test_moverse_expulsar_cantidad_total_de_pokemones();
//    Expulsar/
//
//    La cantidad de pokemones por especie debe bajar cuando se expulsa a alguien con pokemones
//
//            La rareza de un pokemon debe bajar cuando se expulsa a un jugador que lo capturó
//



};

#endif //SRC_TESTSMOVERSE_H
