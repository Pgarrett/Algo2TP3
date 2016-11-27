#include "Juego.h"

Juego::Juego(const Mapa &m) : _mapa(m), _jugadores(Conj<InfoJugador>()), _idsJugadores(Conj<Jugador>()),
                              _expulsados(Conj<Jugador>()), _jugadoresPorID(Vector<InfoVectorJugadores>()),
                              _pokemones(DiccString<Nat>()), _todosLosPokemones(Lista<InfoPokemon>()),
                              _posicionesPokemons(DiccMat<Conj<InfoPokemon>::Iterador>(m.ancho(), m.largo())),
                              _posicionesJugadores(DiccMat<Lista<Jugador>*>(m.ancho(), m.largo())){};

Juego::~Juego() {

}

const Mapa Juego::mapa() const {
    return _mapa;
}

void Juego::agregarPokemon(const Pokemon &p, const Coordenada &c){
    InfoPokemon infoP = InfoPokemon(p,c);
    Lista<typename Juego::InfoPokemon>::Iterador itPokemon = _todosLosPokemones.AgregarAtras(infoP);
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
            ++desdeLat;
        }
        ++desdeLong;
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
    Jugador id = _jugadores.Cardinal() + _expulsados.Cardinal();
    Conj<Jugador>::Iterador itConjIds = _idsJugadores.AgregarRapido(id);
    Conj<InfoJugador>::Iterador itJ = _jugadores.AgregarRapido(InfoJugador(itConjIds));
    _jugadoresPorID.AgregarAtras(InfoVectorJugadores(itJ, ColaMinPrior<Lista<Jugador>::Iterador>().CrearIt()));
    return id;
}

Conj<Jugador> Juego::expulsados() const {
    return _expulsados;
}

bool Juego::estaConectado(const Jugador &j) const {
    return _jugadoresPorID.operator[](j).info.Siguiente().estaConectado;
}

Nat Juego::sanciones(const Jugador &j) const {
    return _jugadoresPorID.operator[](j).info.Siguiente().sanciones;
}

Conj<Jugador> Juego::jugadores() const {
    return _idsJugadores;
}

bool Juego::hayPokemonCercano(const Coordenada &c) const {
    return false;
}

void Juego::conectarse(const Jugador &j, const Coordenada &c) {

}

void Juego::moverse(const Jugador &j, const Coordenada &c) {

}

Coordenada Juego::posicion(const Jugador &j) const {
    return Coordenada(0, 0);
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


