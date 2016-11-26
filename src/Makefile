XXFLAGS = -g -Wall

SOURCES = aed2/ConjAcotado.cpp Driver.cpp tests.cpp test/TestsMapa.cpp test/TestsJuego.cpp modulos/Juego.cpp test/TestsDiccMat.cpp test/TestsDiccString.cpp test/TestsColaMinPrior.cpp modulos/Mapa.cpp #test/TestMoverse.cpp
HEADERS = aed2/Arreglo.h aed2/Conj.h aed2/ConjAcotado.h aed2/Dicc.h aed2/Lista.h aed2/TiposBasicos.h aed2/Vector.h aed2.h Driver.h mini_test.h TiposJuego.h test/TestsMapa.h test/TestsJuego.h modulos/Mapa.h modulos/DiccMat.h modulos/Juego.h modulos/diccString.h test/TestsDiccMat.h test/TestsDiccString.h modulos/ColaMinPrior.h test/TestsColaMinPrior.h #test/TestMoverse.h
OBJS = $(SOURCES:.cpp=.o)

LIBS =

TARGET = eTest

$(TARGET): $(HEADERS) $(OBJS) 
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

valgrind: all
	valgrind --leak-check=full ./$(TARGET)
