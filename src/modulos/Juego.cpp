#include "Juego.h"

Juego::Juego(const Mapa &m) : _mapa(m), _jugadores(Lista<InfoJugador>()), _idsJugadores(Conj<Jugador>()),
                              _expulsados(Conj<Jugador>()), _jugadoresPorID(Vector<InfoVectorJugadores>()),
                              _pokemones(DiccString<Nat>()), _todosLosPokemones(Lista<InfoPokemon>()),
                              _posicionesPokemons(DiccMat<Lista<InfoPokemon>::Iterador>(m.largo(), m.ancho())),
                              _posicionesJugadores(DiccMat<Lista<Jugador> *>(m.largo(), m.ancho())) { };

Juego::~Juego() {
    Conj<Coordenada>::const_Iterador it = _posicionesJugadores.coordenadas();
    while (it.HaySiguiente()) {
        delete _posicionesJugadores.significado(it.Siguiente());
        it.Avanzar();
    }
}

const Mapa Juego::mapa() const {
    return _mapa;
}

void Juego::agregarPokemon(const Pokemon &p, const Coordenada &c){
    InfoPokemon infoP = InfoPokemon(p,c);
    Lista<typename Juego::InfoPokemon>::Iterador itPokemon = _todosLosPokemones.AgregarAtras(infoP);
    _posicionesPokemons.definir(c, itPokemon);
    Nat desdeLat = DamePos(c.latitud, 2);
    Nat desdeLong = DamePos(c.longitud, 2);
    while(desdeLat < (c.latitud + 2)){
        while(desdeLong < (c.longitud + 2)){
            Coordenada cIndex = Coordenada(desdeLat, desdeLong);
            if(DistEuclidea(cIndex, c) <= 4){
                if(_posicionesJugadores.definido(cIndex)){
                    Lista<Jugador>::Iterador itJugadores = (*_posicionesJugadores.significado(cIndex)).CrearIt();
                    while(itJugadores.HaySiguiente()){
                        Jugador e = itJugadores.Siguiente();
                        InfoVectorJugadores tupJugId = _jugadoresPorID[e];
                        Nat cantPokemonesJug = tupJugId.info.Siguiente().pokemonesCapturados.Cardinal();
                        ColaMinPrior<Lista<Jugador>::Iterador>::Iterador itCola = itPokemon.Siguiente().jugadoresEnRango.Encolar(cantPokemonesJug, itJugadores);
                        _jugadoresPorID[e].encolado = itCola;
                        itJugadores.Avanzar();
                    }
                }
            }
            ++desdeLong;
        }
        ++desdeLat;
    }
    if (_pokemones.Definido(p)){
        Nat cViejo = _pokemones.Significado(p);
        _pokemones.Borrar(p);
        _pokemones.Definir(p, cViejo);
    }else{
        _pokemones.Definir(p, 1);
    }
}

Jugador Juego::agregarJugador() {
    Jugador id = _jugadores.Longitud() + _expulsados.Cardinal();
    Conj<Jugador>::Iterador itConjIds = _idsJugadores.AgregarRapido(id);
    Lista<InfoJugador>::Iterador itJ = _jugadores.AgregarAtras(InfoJugador(itConjIds));
    _jugadoresPorID.AgregarAtras(InfoVectorJugadores(itJ, ColaMinPrior<Lista<Jugador>::Iterador>().CrearIt()));
    return id;
}

Conj<Jugador> Juego::expulsados() const {
    return _expulsados;
}

bool Juego::estaConectado(const Jugador &j) const {
    return _jugadoresPorID[j].info.Siguiente().estaConectado;
}

Nat Juego::sanciones(const Jugador &j) const {
    return _jugadoresPorID[j].info.Siguiente().sanciones;
}

Conj<Jugador> Juego::jugadores() const {
    return _idsJugadores;
}

bool Juego::hayPokemonCercano(const Coordenada &c) const {
    bool res = false;
    Nat latC = c.latitud;
    Nat i = DamePos(latC, 2);
    Nat longC = c.longitud;
    Nat j = DamePos(longC, 2);
    while (i <= latC + 2){
        while (j <= longC + 2){
            if (_posicionesPokemons.definido(Coordenada(i, j)) && DistEuclidea(c, Coordenada(i, j)) <= 4){
                res = true;
            }
            j++;
        }
        i++;
        j = DamePos(longC, 2);
    }
    return res;
}

void Juego::conectarse(const Jugador &j, const Coordenada &c) {
    Lista<InfoJugador>::Iterador &itJug = _jugadoresPorID[j].info;
    InfoJugador &infoJ = itJug.Siguiente();
    infoJ.estaConectado = true;
    AgregarJugadorEnPos(_posicionesJugadores, infoJ, c);
    if (hayPokemonCercano(c)) {
        InfoPokemon &p = _posicionesPokemons.significado(posPokemonCercano(c)).Siguiente();
        const ColaMinPrior<Lista<Jugador>::Iterador>::Iterador &iterador = p.jugadoresEnRango.Encolar(infoJ.pokemonesCapturados.Cardinal(), infoJ.itPosicion);
        _jugadoresPorID[j].encolado = iterador;
        p.contador = 0;
    }
}

void Juego::AgregarJugadorEnPos(DiccMat<Lista<Jugador> *> &d, Juego::InfoJugador &j, Coordenada c) {
    if (not d.definido(c)) {
        d.definir(c, new Lista<Jugador>);
    }
    Lista<Jugador>& l = *(d.significado(c));
    j.itPosicion = l.AgregarAtras(j.id.Siguiente());
    j.posicion = c;
}

void Juego::moverse(const Jugador &id, const Coordenada &c) {
    InfoVectorJugadores tupJug = _jugadoresPorID[id];
    InfoJugador& infoJ = tupJug.info.Siguiente();

    if (debeSancionarse(id, c)){
        if (infoJ.sanciones < 4){
            infoJ.sanciones++;
        } else {
            _expulsados.AgregarRapido(infoJ.id.Siguiente());
            infoJ.id.EliminarSiguiente();
            tupJug.info.EliminarSiguiente();
        }
    } else {
        infoJ.itPosicion.EliminarSiguiente();
        AgregarJugadorEnPos(_posicionesJugadores, infoJ, c);
    }
}

Coordenada Juego::posicion(const Jugador &j) const {
    return _jugadoresPorID[j].info.Siguiente().posicion;
}

Nat Juego::cantPokemonsTotales() const {
    return 0;
}

Nat Juego::cantMismaEspecie(const Pokemon &p) const {
    return 0;
}

Conj<Coordenada> Juego::posConPokemons() const {
    return Conj<Coordenada>();
}

Nat Juego::DamePos(const Nat p, const Nat step) const{
    if (p >= step){
        return (p-step);
    }else{
        return 0;
    }
}

Nat Juego::DistEuclidea(const Coordenada c1, const Coordenada c2) const{
    Nat rLa = 0;
    Nat rLo = 0;
    if (c1.latitud > c2.latitud){
        rLa = ((c1.latitud - c2.latitud) * (c1.latitud - c2.latitud));
    }else{
        rLa = ((c2.latitud - c1.latitud) * (c2.latitud - c1.latitud));
    }
    if (c1.longitud > c2.longitud){
        rLo = ((c1.longitud - c2.longitud) * (c1.longitud - c2.longitud));
    }else{
        rLo = ((c2.longitud - c1.longitud) * (c2.longitud - c1.longitud));
    }
    return (rLa + rLo);
}

bool Juego::debeSancionarse(const Jugador j, const Coordenada c) const {
    InfoVectorJugadores t = _jugadoresPorID[j];
    InfoJugador infoJ = t.info.Siguiente();
    return !_mapa.hayCamino(infoJ.posicion, c) || DistEuclidea(infoJ.posicion, c) > 100;
}

Conj<Jugador> Juego::entrenadoresPosibles(const Coordenada &c) const {
    Conj<Jugador> posibles;
    Conj<Jugador>::const_Iterador it = _idsJugadores.CrearIt();
    while (it.HaySiguiente()){
        Jugador idJugador = it.Siguiente();
        InfoJugador infoJ = _jugadoresPorID[idJugador].info.Siguiente();
        if (infoJ.estaConectado){
            Coordenada posJugador = infoJ.posicion;
            if(hayPokemonCercano(posJugador)){
                if (posPokemonCercano(posJugador) == c){
                    if (_mapa.hayCamino(c, posJugador)){
                        posibles.AgregarRapido(idJugador);
                    }
                }
            }
        }
        it.Avanzar();
    }
    return posibles;
}

void Juego::desconectarse(const Jugador &j) {

}

Coordenada Juego::posPokemonCercano(const Coordenada &c) const {
    Coordenada res(0, 0);
    Nat latC = c.latitud;
    Nat i = DamePos(latC, 2);
    Nat longC = c.longitud;
    Nat j = DamePos(longC, 2);
    while (i <= latC + 2) {
        while (j <= longC + 2) {
            if (_posicionesPokemons.definido(Coordenada(i, j)) && DistEuclidea(c, Coordenada(i, j)) <= 4) {
                res = Coordenada(i, j);
            }
            j++;
        }
        i++;
        j = DamePos(longC, 2);
    }
    return res;
}