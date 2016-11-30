#include "Mapa.h"
#include "../aed2.h"

typedef Coordenada Coor;
typedef Conj<Coor>::const_Iterador ItConj;

Mapa::Mapa() : secciones(NULL) {
}

Mapa::Mapa(const Mapa &mapa) {
    secciones = NULL;
    Conj<Coor> coords = mapa.coordenadas();
    ItConj it = coords.CrearIt();
    while (it.HaySiguiente()) {
        agregarCoordenada(it.Siguiente());
        it.Avanzar();
    }
}

void Mapa::agregarCoordenada(const Coordenada &c) {
    coords.Agregar(c);
    redefinirSecciones();
}

void Mapa::redefinirSecciones() {
    delete secciones;
    Nat l = largo();
    Nat a = ancho();
    secciones = new DiccMat<Nat>(l, a);

    DiccMat<bool> coordsMapa(l, a);
    ItConj it1 = coords.CrearIt();
    while (it1.HaySiguiente()) {
        coordsMapa.definir(it1.Siguiente(), true);
        it1.Avanzar();
    }
    Nat seccion = 0;
    ItConj it = coords.CrearIt();
    while (it.HaySiguiente()) {
        Coor c = it.Siguiente();
        if (!secciones->definido(c))
            definirSeccion(coordsMapa, c, seccion++);
        it.Avanzar();
    }
}

void Mapa::definirSeccion(DiccMat<bool> &d, Coordenada c, Nat id) {
    if (d.definido(c) && !secciones->definido(c)) {
        secciones->definir(c, id);
        definirSeccion(d, Coor(c.latitud + 1, c.longitud), id);
        definirSeccion(d, Coor(c.latitud, c.longitud + 1), id);
        if (c.longitud > 0)
            definirSeccion(d, Coor(c.latitud, c.longitud - 1), id);
        if (c.latitud > 0)
            definirSeccion(d, Coor(c.latitud - 1, c.longitud), id);
    }
}

Conj<Coordenada> Mapa::coordenadas() const {
    return coords;
}

bool Mapa::posExistente(const Coordenada &c) const {
    return coords.Pertenece(c);
}

Nat Mapa::ancho() const {
    assert(!coords.EsVacio());
    Nat ancho = 0;
    for (ItConj it = coords.CrearIt(); it.HaySiguiente(); it.Avanzar()) {
        Coor c = it.Siguiente();
        if (c.longitud > ancho)
            ancho = c.longitud;
    }
    return ++ancho;
}

Nat Mapa::largo() const {
    assert(!coords.EsVacio());
    Nat largo = 0;
    for (ItConj it = coords.CrearIt(); it.HaySiguiente(); it.Avanzar()) {
        Coor c = it.Siguiente();
        if (c.latitud > largo)
            largo = c.latitud;
    }
    return ++largo;
}

bool Mapa::hayCamino(const Coordenada &a, const Coordenada &b) const {
#ifdef DEBUG
    assert(coords.Pertenece(a) && coords.Pertenece(b));
#endif
    return secciones->significado(a) == secciones->significado(b);
}

Mapa::~Mapa() {
    delete secciones;
}