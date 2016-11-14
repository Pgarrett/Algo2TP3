#ifndef SRC_MAPA_H
#define SRC_MAPA_H

#include "../TiposJuego.h"
#include "../aed2/Conj.h"

class Mapa {

public:
    Mapa();
    ~Mapa();
    void agregarCoordenada(const Coordenada& c);
    Conj<Coordenada> coordenadas() const;
    bool posExistente(const Coordenada& c) const;
    bool hayCamino(const Coordenada& a, const Coordenada& b) const;
    Nat ancho() const;
    Nat largo() const;

private:
    Conj<Coordenada> coords;
};


#endif //SRC_MAPA_H
