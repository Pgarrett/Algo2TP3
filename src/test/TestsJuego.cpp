#include "TestsJuego.h"
#include "../mini_test.h"
#include "../Driver.h"

void TestsJuego::correr_tests() {
    RUN_TEST(test_constructor_con_mapa);
    RUN_TEST(test_agregar_jugadores);
    RUN_TEST(test_agregar_pokemones);
}

void TestsJuego::test_constructor_con_mapa() {
    Conj<Coordenada> cc;
    cc.Agregar(Coordenada(0,0));
    cc.Agregar(Coordenada(0,1));
    cc.Agregar(Coordenada(0,2));
    cc.Agregar(Coordenada(1,2));
    cc.Agregar(Coordenada(10,0));
    cc.Agregar(Coordenada(1,4));

    Driver d(cc);
    ASSERT( false );
//  ASSERT( d.mapa() == cc );
}

void TestsJuego::test_agregar_jugadores(){
    ASSERT( false );
}

void TestsJuego::test_agregar_pokemones(){
    ASSERT( false );
}


