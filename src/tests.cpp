// Compilar usando:
//	g++ -o tests tests.cpp Driver.cpp <lista de archivos *.cpp propios>
//	valgrind --leak-check=full ./tests

#include "Driver.h"
#include "mini_test.h"

using namespace aed2;

void test_constructor_con_mapa() {
  Conj<Coordenada> cc;
  cc.Agregar(Coordenada(0,0));
  cc.Agregar(Coordenada(0,1));
  cc.Agregar(Coordenada(0,2));
  cc.Agregar(Coordenada(1,2));
  cc.Agregar(Coordenada(10,0));
  cc.Agregar(Coordenada(1,4));
  Driver d(cc);
  ASSERT( d.mapa() == cc );
}

void test_agregar_jugadores(){
	ASSERT( false );
}

void test_agregar_pokemones(){
	ASSERT( false );
}

// TODO: Agregar más tests


int main(int argc, char **argv)
{
  RUN_TEST(test_constructor_con_mapa);
  RUN_TEST(test_agregar_jugadores);
  RUN_TEST(test_agregar_pokemones);
  
  return 0;
}
