#ifndef DICC_STRING_H
#define DICC_STRING_H


#include "../aed2.h"
#include <string>

using namespace std;
using namespace aed2;

#define NHIJOS 256

template<typename T>
class DiccString {

public:

    DiccString();

    ~DiccString();

    DiccString(const DiccString<T> &otro);

    DiccString<T> &operator=(const DiccString<T> &otro);

    bool Definido(const string &clave) const;

    void Definir(const string &clave, const T &significado);

    const T &Significado(const string &clave) const;

    T &Significado(const string &clave);

    void Borrar(const string &clave);

    Conj<String>::const_Iterador CrearItClaves() const;

    const string &ClaveMinima() const;

    const string &ClaveMaxima() const;

private:

    struct Nodo {

        Nodo(Nodo *_padre, Nat _idx)
                : hijos(Arreglo<Nodo *>(NHIJOS)), info(NULL), padre(_padre), idx(_idx) {
            Nat i = 0;
            while (i < NHIJOS) {
                hijos.Definir(i, NULL);
                i++;
            }
        };

        bool TieneHijos() {
            Nat i = 0;
            while (i < NHIJOS && hijos[i] == NULL) i++;
            return i < NHIJOS;
        }

        Arreglo<Nodo *> hijos;
        T *info;
        Conj<String>::Iterador clave;
        Nodo *padre;
        Nat idx;

    };

    Nodo *raiz;
    Conj<string> claves;
    string min;
    string max;

    Nodo *buscar(Nodo *n, const string &clave) const;

    Nodo *crear(Nodo *n, const string &clave);

    void ActualizarMin();

    void ActualizarMax();

    void BorrarTodo();

    void AgregarTodoDe(const DiccString<T> &otro);
};

template<class T>
bool operator==(const DiccString<T> &d, const DiccString<T> &d2);

//Constructor vacio
template<class T>
DiccString<T>::DiccString()
        : raiz(new Nodo(NULL, 0)) {

}

//Destructor
template<typename T>
DiccString<T>::~DiccString() {
    BorrarTodo();
    delete raiz;
    raiz = NULL;
}

//Borra todoas las entradas del diccionario
template<typename T>
void DiccString<T>::BorrarTodo() {

    //Guardo en un conjunto todas las claves actuales
    Conj<String>::const_Iterador it = CrearItClaves();
    Conj<String> aBorrar;
    while (it.HaySiguiente()) {
        string clave = it.Siguiente();
        aBorrar.AgregarRapido(clave);
        it.Avanzar();
    }
    //Borro todas las entradas del diccionario
    Conj<String>::Iterador it2 = aBorrar.CrearIt();
    while (it2.HaySiguiente()) {
        Borrar(it2.Siguiente());
        it2.Avanzar();
    }
}

//Agrego todas las entradas de otro diccionario
template<typename T>
void DiccString<T>::AgregarTodoDe(const DiccString<T> &otro) {
    Conj<String>::const_Iterador it = otro.CrearItClaves();
    while (it.HaySiguiente()) {
        string clave = it.Siguiente();
        const T &significado = otro.Significado(clave);
        Definir(clave, significado);
        it.Avanzar();
    }
}

//Copy constructor
template<typename T>
DiccString<T>::DiccString(const DiccString<T> &otro)
        : raiz(new Nodo(NULL, 0)) {
    AgregarTodoDe(otro);
}

//Operador de asignacion
template<typename T>
DiccString<T> &DiccString<T>::operator=(const DiccString<T> &otro) {
    if (this != &otro) {
        BorrarTodo();
        AgregarTodoDe(otro);
    }
    return *this;
}

//Operador de comparacion
template<class T>
bool operator==(const DiccString<T> &d1, const DiccString<T> &d2) {
    Conj<String>::const_Iterador it1 = d1.CrearItClaves();
    Conj<String>::const_Iterador it2 = d2.CrearItClaves();
    while (it1.HaySiguiente()) {
        string c1 = it1.Siguiente();
        if (d1.Significado(c1) != d2.Significado(c1)) {
            return false;
        }
        it1.Avanzar();
    }

    while (it2.HaySiguiente()) {
        string c2 = it2.Siguiente();
        if (d1.Significado(c2) != d2.Significado(c2)) {
            return false;
        }
        it2.Avanzar();
    }

    return true;
}


//Busca si existe una clave
template<typename T>
typename DiccString<T>::Nodo *DiccString<T>::buscar(typename DiccString<T>::Nodo *n, const string &clave) const {
    Nat i = 0;
    //cout << "Clave:" << clave << " Size: " << clave.size() << endl;
    while (i < clave.size() && n != NULL) {
        Nat idx = (Nat) clave[i];
        n = n->hijos[idx];
        i++;
    }
    return n;
}

//Crea un nodo para la clave
template<typename T>
typename DiccString<T>::Nodo *DiccString<T>::crear(typename DiccString<T>::Nodo *n, const string &clave) {
    Nat i = 0;
    while (i < clave.size() && n != NULL) {
        Nat idx = (Nat) clave[i];
        if (n->hijos[idx] == NULL) {
            n->hijos[idx] = new Nodo(n, idx);
        }
        n = n->hijos[idx];
        i++;
    }
    return n;

}

//Devuelve si esta dfinida una clave
template<typename T>
bool DiccString<T>::Definido(const string &clave) const {
    Nodo *n = buscar(raiz, clave);
    return n != NULL && n->info != NULL;
}

//Define una clave
template<typename T>
void DiccString<T>::Definir(const string &clave, const T &s) {
    Nodo *n = crear(raiz, clave);
    if (n->info == NULL) {
        n->info = new T(s);
        n->clave = claves.AgregarRapido(clave);
        ActualizarMin();
        ActualizarMax();
    } else {
        delete n->info;
        n->info = new T(s);
    }
}

//Devuelve el significado de una clave
template<typename T>
const T &DiccString<T>::Significado(const string &clave) const {
    Nodo *n = buscar(raiz, clave);
    return *(n->info);
}

template<typename T>
T &DiccString<T>::Significado(const string &clave) {
    Nodo *n = buscar(raiz, clave);
    return *(n->info);
}


//Borra una clave
template<typename T>
void DiccString<T>::Borrar(const string &clave) {
    Nodo *n = buscar(raiz, clave);
    delete n->info;
    n->info = NULL;
    n->clave.EliminarSiguiente();
    while (n != NULL && !(n->TieneHijos()) && (n->info == NULL)) {
        Nodo *padre = n->padre;
        if (padre != NULL) {
            Nat idx = n->idx;
            delete padre->hijos[n->idx];
            padre->hijos[idx] = NULL;
        }
        n = padre;
    }
    ActualizarMin();
    ActualizarMax();
}


//Actualiza la clave minima
template<typename T>
void DiccString<T>::ActualizarMin() {
    min = "";
    if (claves.Cardinal() > 0) {
        Nodo *n = raiz;
        while (n->info == NULL) {
            Nat i = 0;
            while (i < NHIJOS && n->hijos[i] == NULL) i++;
            n = n->hijos[i];
        }
        min = n->clave.Siguiente();
    }
}

//Actualiza la clave maxima
template<typename T>
void DiccString<T>::ActualizarMax() {
    max = "";
    if (claves.Cardinal() > 0) {
        Nodo *n = raiz;
        while (n->TieneHijos()) {
            Nat i = 0;
            while (i < NHIJOS && n->hijos[NHIJOS - i - 1] == NULL) i++;
            n = n->hijos[NHIJOS - i - 1];
        }
        max = n->clave.Siguiente();
    }
}

//Crea un iterador al conjunto de claves
template<typename T>
Conj<String>::const_Iterador DiccString<T>::CrearItClaves() const {
    return claves.CrearIt();
}

template<typename T>
const string &DiccString<T>::ClaveMinima() const {
    return min;
}

template<typename T>
const string &DiccString<T>::ClaveMaxima() const {
    return max;
}


#endif //DICC_STRING_H