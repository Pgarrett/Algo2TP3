// Compilar usando:
//	g++ -o tests tests.cpp Driver.cpp test/*.cpp modulos/*.cpp <lista de archivos *.cpp propios>
//	valgrind --leak-check=full ./tests

#include "test/TestsMapa.h"
#include "test/TestsJuego.h"

int main(int argc, char **argv)
{
  TestsMapa::correr_tests();
//  TestsJuego::correr_tests();
  return 0;
}
