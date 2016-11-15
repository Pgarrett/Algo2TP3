#ifndef SRC_DICCMAT_H
#define SRC_DICCMAT_H

#include "../TiposJuego.h"
#include "../aed2/Conj.h"

template<class T>
class DiccMat {

public:
    DiccMat(Nat ancho, Nat largo);

    ~DiccMat();

    const Conj<Coordenada>::const_Iterador coordenadas() const;

    const Nat ancho() const;

    const Nat largo() const;

    const bool definido(const Coordenada &c) const;

    void definir(const Coordenada &c, const T t);

    const T significado(const Coordenada &c) const;

    void borrar(const Coordenada &c);

private:
    const Nat _ancho, _largo;
    Conj<Coordenada> claves;

    struct Tupla {
        bool usado;
        Conj<Coordenada>::Iterador it;
        T valor;

        Tupla() : usado(false) { }
    };

    typename DiccMat::Tupla *_valores;

    inline bool enRango(Coordenada c) const {
        return c.latitud < _largo && c.longitud < _ancho;
    }

    inline Nat aplanar(const Coordenada c) const {
        return c.longitud * _ancho + c.latitud;
    }

};

template<class T>
DiccMat<T>::DiccMat(Nat largo, Nat ancho) : _ancho(ancho), _largo(largo) {
    assert(ancho > 0 && largo > 0);
    _valores = new Tupla[_ancho * _largo];
    for (unsigned int i = 0; i < _ancho * _largo; i++)
        _valores[i] = Tupla();
}

template<class T>
DiccMat<T>::~DiccMat() {
    delete[] _valores;
}

template<class T>
const Nat DiccMat<T>::ancho() const {
    return _ancho;
}

template<class T>
const Nat DiccMat<T>::largo() const {
    return _largo;
}

template<class T>
const Conj<Coordenada>::const_Iterador DiccMat<T>::coordenadas() const {
    return claves.CrearIt();
}

template<class T>
const bool DiccMat<T>::definido(const Coordenada &c) const {
    assert(enRango(c));
    return _valores[aplanar(c)].usado;
}

template<class T>
void DiccMat<T>::definir(const Coordenada &c, const T t) {
    assert(enRango(c));
    if (!definido(c))
        _valores[aplanar(c)].it = claves.AgregarRapido(c);
    _valores[aplanar(c)].usado = true;
    _valores[aplanar(c)].valor = t;
}

template<class T>
const T DiccMat<T>::significado(const Coordenada &c) const {
    assert(definido(c));
    return _valores[aplanar(c)].valor;
}

template<class T>
void DiccMat<T>::borrar(const Coordenada &c) {
    assert(definido(c));
    _valores[aplanar(c)].usado = false;
    _valores[aplanar(c)].it.EliminarSiguiente();
}

#endif //SRC_DICCMAT_H