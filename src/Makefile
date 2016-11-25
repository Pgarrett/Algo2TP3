XXFLAGS = -g -Wall

SOURCES = aed2/Arreglo.h aed2/Conj.h aed2/ConjAcotado.cpp aed2/ConjAcotado.h aed2/Dicc.h aed2/Lista.h aed2/TiposBasicos.h aed2/Vector.h aed2.h Driver.cpp Driver.h mini_test.h tests.cpp TiposJuego.h test/TestsMapa.cpp test/TestsMapa.h test/TestsJuego.cpp test/TestsJuego.h modulos/Mapa.cpp modulos/Mapa.h modulos/DiccMat.h modulos/Juego.cpp modulos/Juego.h modulos/diccString.h test/TestsDiccMat.cpp test/TestsDiccMat.h test/TestsDiccString.cpp test/TestsDiccString.h modulos/ColaMinPrior.h test/TestsColaMinPrior.cpp test/TestsColaMinPrior.h
OBJS = $(SOURCES:.cpp=.o)

LIBS =

TARGET = eTest

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

valgrind: all
	valgrind --leak-check=full ./$(TARGET)
