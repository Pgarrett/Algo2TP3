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

    void definir(const Coordenada &c, const T t) const;

private:
    const Nat _ancho, _largo;

    struct Tupla {
        bool usado;
        T t;

        Tupla() : usado(false) {}
    };

    typename DiccMat::Tupla *_valores;

    inline bool enRango(Coordenada c) const {
        return c.latitud < _largo && c.longitud < _ancho;
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
    Conj<Coordenada> a;
    return a.CrearIt();
}

template<class T>
const bool DiccMat<T>::definido(const Coordenada &c) const {
    assert(enRango(c));
    return _valores[0].usado;
}

template<class T>
void DiccMat<T>::definir(const Coordenada &c, const T t) const {
    assert(enRango(c));
    _valores[0].usado = true;
    _valores[0].t = t;
}

#endif //SRC_DICCMAT_H
