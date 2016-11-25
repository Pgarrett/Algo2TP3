// Compilar usando:
//	g++ -o tests tests.cpp Driver.cpp test/*.cpp modulos/*.cpp <lista de archivos *.cpp propios>
//	valgrind --leak-check=full ./tests

#include "test/TestsMapa.h"
#include "test/TestsJuego.h"
#include "test/TestsDiccMat.h"
#include "test/TestsDiccString.h"
#include "test/TestsColaMinPrior.h"

int main(int argc, char **argv)
{
  TestsDiccMat::correr_tests();
  TestsDiccString::correr_tests();
  TestsColaMinPrior::correr_tests();
  TestsMapa::correr_tests();
  TestsJuego::correr_tests();
  return 0;
}
