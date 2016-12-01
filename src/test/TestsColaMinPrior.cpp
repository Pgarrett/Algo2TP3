#include <iostream>
#include <fstream>
#include <cstdlib>
#include "TestsColaMinPrior.h"
#include "../modulos/ColaMinPrior.h"
#include "../mini_test.h"

using namespace std;
using namespace aed2;

void TestsColaMinPrior::correr_tests() {
//    RUN_TEST(test_cola_min_prior_crear);
//    RUN_TEST(test_cola_min_prior_encolar);
//    RUN_TEST(test_cola_min_prior_desencolar);
//    RUN_TEST(test_cola_min_prior_desencolar_dos);
//    RUN_TEST(test_cola_min_prior_iterator_eliminarSig);
//    RUN_TEST(test_cola_min_prior_iterator);
//    RUN_TEST(test_cola_min_prior_iterator_eliminarTodoDesdeElIt);
//    RUN_TEST(test_cola_min_prior_violento);
    RUN_TEST(test_encolar)
}

void TestsColaMinPrior::test_cola_min_prior_crear() {
    ColaMinPrior<int> cl;
    ASSERT(!false);
}

void TestsColaMinPrior::test_cola_min_prior_encolar() {
    ColaMinPrior<int> cl;
    cl.Encolar(4, 1);
    cl.Encolar(2, 2);
    cl.Encolar(6, 3);
    cl.Encolar(5, 4);
    cl.Encolar(4, 5);
    cl.Encolar(23, 6);
    cl.Encolar(1, 7);
    ASSERT(cl.Tamano() == 7);
}

void TestsColaMinPrior::test_cola_min_prior_desencolar() {
    ColaMinPrior<int> cl;
    cl.Encolar(4, 1);
    cl.Desencolar();
    cl.Encolar(2, 2);
    cl.Encolar(6, 3);
    cl.Encolar(5, 4);
    ASSERT(cl.Tamano() == 3);
    cl.Desencolar();
    ASSERT(cl.Tamano() == 2);
}

void TestsColaMinPrior::test_cola_min_prior_desencolar_dos() {
    ColaMinPrior<int> cl;
    cl.Encolar(4, 1);
    cl.Encolar(2, 2);
    cl.Encolar(6, 3);
    cl.Encolar(5, 4);
    cl.Encolar(4, 5);
    cl.Encolar(23, 6);
    cl.Encolar(1, 7);
    ASSERT(cl.Tamano() == 7);
//	cout << "Encolar: " << cl << endl;
    cl.Encolar(15, 8);
    cl.Encolar(16, 9);
    cl.Encolar(31, 10);
    ASSERT(cl.Tamano() == 10);
//	cout << "Encolar mas: " << cl << endl;
    cl.Desencolar();
    ASSERT(cl.Tamano() == 9);
//	cout << "Desncolar: " << endl << cl << endl;
    while (!cl.EsVacia()) {
        cl.Desencolar();
    }
//	cout << "Desncolar todo: " << endl << cl << endl;
}

void TestsColaMinPrior::test_cola_min_prior_iterator_eliminarSig() {
    ColaMinPrior<int> cl;
    typename ColaMinPrior<int>::Iterador it;
    it = cl.Encolar(4, 1);
    it.EliminarSiguiente();
}

void TestsColaMinPrior::test_cola_min_prior_iterator() {
    ColaMinPrior<int> cl;
    typename ColaMinPrior<int>::Iterador it;
//	cout << endl;
    it = cl.Encolar(4, 1);
//	cout << "it.Siguiente = " << it.Siguiente() <<endl;
    it = cl.Encolar(2, 2);
//	cout << "it.Siguiente = " << it.Siguiente() <<endl;
    it = cl.Encolar(6, 3);
//	cout << "it.Siguiente = " << it.Siguiente() <<endl;
    it = cl.Encolar(5, 4);
//	cout << "it.Siguiente = " << it.Siguiente() <<endl;
    it = cl.Encolar(4, 5);
//	cout << "it.Siguiente = " << it.Siguiente() <<endl;
    it = cl.Encolar(23, 6);
//	cout << "it.Siguiente = " << it.Siguiente() <<endl;
    it = cl.Encolar(1, 7);
//	cout << "it.Siguiente = " << it.Siguiente() <<endl;
//	cout << cl << endl;
    ASSERT(cl.Tamano() == 7);

    it.EliminarSiguiente();
    ASSERT(cl.Tamano() == 6);
//	cout << cl << endl;
}

void TestsColaMinPrior::test_cola_min_prior_iterator_eliminarTodoDesdeElIt() {
    ColaMinPrior<int> cl;
    typename ColaMinPrior<int>::Iterador it;
    typename ColaMinPrior<int>::Iterador it1 = cl.Encolar(4, 1);
    typename ColaMinPrior<int>::Iterador it2 = cl.Encolar(2, 2);
    typename ColaMinPrior<int>::Iterador it3 = cl.Encolar(6, 3);
    typename ColaMinPrior<int>::Iterador it4 = cl.Encolar(5, 4);
    typename ColaMinPrior<int>::Iterador it5 = cl.Encolar(14, 5);
    typename ColaMinPrior<int>::Iterador it6 = cl.Encolar(23, 6);
    typename ColaMinPrior<int>::Iterador it7 = cl.Encolar(12, 7);
    //cout << cl << endl;

    int ctrlRaiz = 2;
    ASSERT(cl.Tamano() == 7 && cl.Proximo() == ctrlRaiz);

//	cout << "tamaño = " << cl.Tamano() << endl;
//	cout << "proximo = " << cl.Proximo() << " deberia ser? " << ctrlRaiz << endl << "--a deletear! " << endl;

    it1.EliminarSiguiente();
    ctrlRaiz = 2;
//	cout << "tamaño = " << cl.Tamano() << endl;
//	cout << "proximo = " << cl.Proximo() << " deberia ser? " << ctrlRaiz << endl;
//	cout << "hay siguiente?" << it1.HaySiguiente() << endl;
    ASSERT(cl.Tamano() == 6 && cl.Proximo() == ctrlRaiz && !it1.HaySiguiente());

    it2.EliminarSiguiente();
    ctrlRaiz = 4;
//	cout << "tamaño = " << cl.Tamano() << endl;
//	cout << "proximo = " << cl.Proximo() << " deberia ser? " << ctrlRaiz << endl;
//	cout << "hay siguiente?" << it2.HaySiguiente() << endl;
    ASSERT(cl.Tamano() == 5 && cl.Proximo() == ctrlRaiz && !it2.HaySiguiente());

    it3.EliminarSiguiente();
    ctrlRaiz = 4;
//	cout << "tamaño = " << cl.Tamano() << endl;
//	cout << "proximo = " << cl.Proximo() << " deberia ser? " << ctrlRaiz << endl;
//	cout << "hay siguiente?" << it3.HaySiguiente() << endl;
    ASSERT(cl.Tamano() == 4 && cl.Proximo() == ctrlRaiz && !it3.HaySiguiente());

    it4.EliminarSiguiente();
    ctrlRaiz = 7;
//	cout << "tamaño = " << cl.Tamano() << endl;
//	cout << "proximo = " << cl.Proximo() << " deberia ser? " << ctrlRaiz << endl;
//	cout << "hay siguiente?" << it4.HaySiguiente() << endl;
    ASSERT(cl.Tamano() == 3 && cl.Proximo() == ctrlRaiz && !it4.HaySiguiente());

    it5.EliminarSiguiente();
    ctrlRaiz = 7;
//	cout << "tamaño = " << cl.Tamano() << endl;
//	cout << "proximo = " << cl.Proximo() << " deberia ser? " << ctrlRaiz << endl;
//	cout << "hay siguiente?" << it5.HaySiguiente() << endl;
    ASSERT(cl.Tamano() == 2 && cl.Proximo() == ctrlRaiz && !it5.HaySiguiente());

    it6.EliminarSiguiente();
    ctrlRaiz = 7;
//	cout << "tamaño = " << cl.Tamano() << endl;
//	cout << "proximo = " << cl.Proximo() << " deberia ser? " << ctrlRaiz << endl;
//	cout << "hay siguiente?" << it6.HaySiguiente() << endl;
    ASSERT(cl.Tamano() == 1 && cl.Proximo() == ctrlRaiz && !it6.HaySiguiente());

    it7.EliminarSiguiente();
//	cout << "tamaño = " << cl.Tamano() << endl;
//	cout << "proximo? = " << cl.EsVacia() << endl;
//	cout << "hay siguiente?" << it7.HaySiguiente() << endl;
    ASSERT(cl.Tamano() == 0 && cl.EsVacia() && !it7.HaySiguiente());

//	cout << cl << endl;
}

void TestsColaMinPrior::test_cola_min_prior_violento() {
    Lista<typename ColaMinPrior<int>::Iterador> temp;
    int i = 1;
    ColaMinPrior<int> cl;
    while (i < 2001) {
        temp.AgregarAdelante(cl.Encolar((rand() % i), i));
        ++i;
    }

//	cout << cl << endl;

    temp[99].EliminarSiguiente();
    temp[199].EliminarSiguiente();
    temp[399].EliminarSiguiente();
    temp[499].EliminarSiguiente();
    temp[959].EliminarSiguiente();
    temp[1050].EliminarSiguiente();

    ASSERT(cl.Tamano() == 1994);
//	cout << cl << endl;

    while (cl.Tamano() > 4) {
        cl.Desencolar();
    }
    ASSERT(cl.Tamano() == 4);
//	cout << cl << endl;
}

void TestsColaMinPrior::test_encolar() {
    ColaMinPrior<int> cl;
    cl.Encolar(4, 1);
    cl.Encolar(2, 2);
    cl.Encolar(6, 3);
    cl.Encolar(5, 4);
    cl.Encolar(4, 5);
    cl.Encolar(23, 6);
    cl.Encolar(1, 7);
    ASSERT_EQ(cl.Proximo(), 7);
}





