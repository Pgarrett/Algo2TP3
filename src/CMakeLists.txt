cmake_minimum_required(VERSION 3.5)
project(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++03")

set(SOURCE_FILES
    aed2/Arreglo.h
    aed2/Conj.h
    aed2/ConjAcotado.cpp
    aed2/ConjAcotado.h
    aed2/Dicc.h
    aed2/Lista.h
    aed2/TiposBasicos.h
    aed2/Vector.h
    aed2.h
    Driver.cpp
    Driver.h
    mini_test.h
    tests.cpp
    TiposJuego.h test/TestsMapa.cpp test/TestsMapa.h test/TestsJuego.cpp test/TestsJuego.h modulos/Mapa.cpp modulos/Mapa.h)

add_executable(src ${SOURCE_FILES})
add_definitions(-std=c++03)