#include "Juego.h"

Juego::Juego(const Mapa &m) : _mapa(m), _jugadores(Lista<InfoJugador>()), _idsJugadores(Conj<Jugador>()),
                              _expulsados(Conj<Jugador>()), _jugadoresPorID(Vector<InfoVectorJugadores>()),
                              _pokemones(DiccString<Nat>()), _todosLosPokemones(Lista<InfoPokemon>()),
                              _posicionesPokemons(DiccMat<Lista<InfoPokemon>::Iterador>(m.largo(), m.ancho())),
                              _posicionesJugadores(DiccMat<Lista<Jugador> *>(m.largo(), m.ancho())) { };

Juego::~Juego() {
    Conj<Coordenada> cs = _posicionesJugadores.coordenadas();
    Conj<Coordenada>::const_Iterador it = cs.CrearIt();
    while (it.HaySiguiente()) {
        delete _posicionesJugadores.significado(it.Siguiente());
        it.Avanzar();
    }
}

const Mapa Juego::mapa() const {
    return _mapa;
}

void Juego::agregarPokemon(const Pokemon &p, const Coordenada &c){
    #ifdef DEBUG
    assert(puedoAgregarPokemon(c));
    #endif

    InfoPokemon infoP = InfoPokemon(p,c);
    Lista<typename Juego::InfoPokemon>::Iterador itPokemon = _todosLosPokemones.AgregarAtras(infoP);
    _posicionesPokemons.definir(c, itPokemon);
    Nat desdeLat = DamePos(c.latitud, 2);
    Nat desdeLong = DamePos(c.longitud, 2);
    while(desdeLat <= (c.latitud + 2)){
        while(desdeLong <= (c.longitud + 2)){
            Coordenada cIndex = Coordenada(desdeLat, desdeLong);
            if(DistEuclidea(cIndex, c) <= 4){
                if(_posicionesJugadores.definido(cIndex) && mapa().hayCamino(c, cIndex)){
                    Lista<Jugador>::Iterador itJugadores = (*_posicionesJugadores.significado(cIndex)).CrearIt();
                    while(itJugadores.HaySiguiente()){
                        Jugador e = itJugadores.Siguiente();
                        InfoVectorJugadores tupJugId = _jugadoresPorID[e];
                        Nat cantPokemonesJug = tupJugId.info.Siguiente().pokemonesCapturados.Longitud();
                        ColaMinPrior<Lista<Jugador>::Iterador>::Iterador itCola = itPokemon.Siguiente().jugadoresEnRango.Encolar(cantPokemonesJug, itJugadores);
                        _jugadoresPorID[e].encolado = itCola;
                        itJugadores.Avanzar();
                    }
                }
            }
            ++desdeLong;
        }
        ++desdeLat;
        desdeLong = DamePos(c.longitud, 2);
    }
    if (_pokemones.Definido(p)){
        Nat cViejo = _pokemones.Significado(p);
        _pokemones.Borrar(p);
        _pokemones.Definir(p, cViejo + 1);
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
    if (hayPokemonCercano(c) && mapa().hayCamino(c, posPokemonCercano(c))){
        InfoPokemon &p = _posicionesPokemons.significado(posPokemonCercano(c)).Siguiente();
        const ColaMinPrior<Lista<Jugador>::Iterador>::Iterador &iterador = p.jugadoresEnRango.Encolar(infoJ.pokemonesCapturados.Longitud(), infoJ.itPosicion);
        _jugadoresPorID[j].encolado = iterador;
        p.contador = 0;
    }
}

void Juego::AgregarJugadorEnPos(DiccMat<Lista<Jugador> *> &d, Juego::InfoJugador &j, Coordenada c) {
    if (not d.definido(c)) {
        d.definir(c, new Lista<Jugador>());
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
        } else { // Expulsar
            Lista<Lista<InfoPokemon>::Iterador>::Iterador itPCapturados  = infoJ.pokemonesCapturados.CrearIt();
            while(itPCapturados.HaySiguiente()){
                InfoPokemon &infoP = itPCapturados.Siguiente().Siguiente();
                Nat pViejos = _pokemones.Significado(infoP.tipo);
                _pokemones.Borrar(infoP.tipo);
                if (pViejos != 1){
                    _pokemones.Definir(infoP.tipo, pViejos - 1);
                }
                itPCapturados.Siguiente().EliminarSiguiente();
                itPCapturados.Avanzar();
            }

            _expulsados.AgregarRapido(infoJ.id.Siguiente());
            infoJ.id.EliminarSiguiente();
            infoJ.itPosicion.EliminarSiguiente();

            if (hayPokemonCercano(infoJ.posicion)) { // Si estaba esperando para atrapar
                tupJug.encolado.EliminarSiguiente();
            }
            tupJug.info.EliminarSiguiente();
        }
    } else {
        if (hayPokemonCercano(c) && mapa().hayCamino(c, posPokemonCercano(c))){ // Va a estar o seguir en un rango
            Coordenada p = posPokemonCercano(c);
            if (!hayPokemonCercano(infoJ.posicion)){ // No estaba en un rango antes
                InfoPokemon &infoP = _posicionesPokemons.significado(p).Siguiente();
                infoP.contador = 0;
            }
            ActualizarMenos(c);
        } else { // No va a estar en un rango
            if (hayPokemonCercano(infoJ.posicion)){ // Salio de un rango
                tupJug.encolado.EliminarSiguiente();
            }
            ActualizarTodos();
        }
        infoJ.itPosicion.EliminarSiguiente();
        AgregarJugadorEnPos(_posicionesJugadores, infoJ, c);
    }
}

Coordenada Juego::posicion(const Jugador &j) const {
    return _jugadoresPorID[j].info.Siguiente().posicion;
}

Nat Juego::cantPokemonsTotales() const {
    return _todosLosPokemones.Longitud();
}

Nat Juego::cantMismaEspecie(const Pokemon &p) const {
    if(_pokemones.Definido(p))
        return _pokemones.Significado(p);
    else
        return 0;
}

Conj<Coordenada> Juego::posConPokemons() const {
    return _posicionesPokemons.coordenadas();
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
/*
Lista<Jugador>::const_Iterador Juego::jugadoresEnPos(const Coordenada &c) const {
    return _posicionesJugadores.significado(c)->CrearIt();
}*/

bool Juego::puedoAgregarPokemon(const Coordenada &c) const{
    return (_mapa.posExistente(c) && (!_posicionesPokemons.definido(c)) && !hayPokemonEnTerritorio(c));
}

bool Juego::hayPokemonEnTerritorio(const Coordenada &c) const{
    bool res = false;
    Nat latC = c.latitud;
    Nat i = DamePos(latC, 5);
    Nat longC = c.longitud;
    Nat j = DamePos(longC, 5);
    while (i <= (latC + 5)) {
        while (j <= (longC + 5)) {
            if (_posicionesPokemons.definido(Coordenada(i, j)) && DistEuclidea(c, Coordenada(i, j)) <= 25) {
                res = true;
            }
            ++j;
        }
        ++i;
        j = DamePos(longC, 5);
    }

    return (res);
}

Lista<Jugador>::const_Iterador Juego::jugadoresEnPos(const Coordenada &c) const {
    return _posicionesJugadores.significado(c)->CrearIt();
}

void Juego::desconectarse(const Jugador &j) {
    InfoVectorJugadores ivf = _jugadoresPorID.operator[](j);
    if (hayPokemonCercano(ivf.info.Siguiente().posicion)) {
        ivf.encolado.EliminarSiguiente();   // TODO checkear si verdaderamente lo elimina, o hay que tengo que trabajar con la referencia de InfoVectorJugadores
    }
    InfoJugador& infoJ = ivf.info.Siguiente();
    infoJ.estaConectado = false;
    infoJ.itPosicion.EliminarSiguiente();
    infoJ.itPosicion = Lista<Jugador>().CrearIt();
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

Pokemon Juego::pokemonEnPos(const Coordenada &c) const{
    #ifdef DEBUG
    assert(posConPokemons().Pertenece(c));
    #endif
    return _posicionesPokemons.significado(c).Siguiente().tipo;
}

Nat Juego::cantMovimientosParaCaptura(const Coordenada &c) const {
    #ifdef DEBUG
    assert(posConPokemons().Pertenece(c));
    #endif
    if(!_posicionesPokemons.significado(c).Siguiente().jugadoresEnRango.EsVacia())
        return (10 - _posicionesPokemons.significado(c).Siguiente().contador);
    else
        return 0;
}

Nat Juego::indiceRareza(const Pokemon &p) const{
    #ifdef DEBUG
    assert(perteneceAPokemons(p));
    #endif
    Nat cuantosP = cantMismaEspecie(p);
    return(100 - (100 * cuantosP / cantPokemonsTotales()));
}

bool Juego::perteneceAPokemons(const Pokemon &p) const{
    Lista<InfoPokemon>::const_Iterador it = _todosLosPokemones.CrearIt();
    bool encontrado = false;
    while(it.HaySiguiente() && !encontrado){
        encontrado = (it.Siguiente().tipo == p);
        it.Avanzar();
    }
    return (encontrado);
}

void Juego::ActualizarPokemon(Lista<InfoPokemon>::Iterador itPokemones){
    InfoPokemon& infoP = itPokemones.Siguiente();
    ++infoP.contador;
    if(!infoP.jugadoresEnRango.EsVacia() && infoP.contador == 10){
        Lista<Jugador>::Iterador e = infoP.jugadoresEnRango.Proximo();
        infoP.salvaje = false;
        InfoJugador& infoJ = _jugadoresPorID[e.Siguiente()].info.Siguiente();
        infoJ.pokemonesCapturados.AgregarAtras(itPokemones);
        _posicionesPokemons.borrar(infoP.posicion);
    }
}

void Juego::ActualizarTodos(){
    Conj<Coordenada> cs = _posicionesPokemons.coordenadas();
    Conj<Coordenada>::Iterador itCoor = cs.CrearIt();
    while(itCoor.HaySiguiente()){
        Lista<InfoPokemon>::Iterador itPokemon = _posicionesPokemons.significado(itCoor.Siguiente());
        ActualizarPokemon(itPokemon);
        itCoor.Avanzar();
    }
}

void Juego::ActualizarMenos(const Coordenada &c){
    Coordenada p = posPokemonCercano(c);
    Conj<Coordenada> cs = _posicionesPokemons.coordenadas();
    Conj<Coordenada>::Iterador itCoor = cs.CrearIt();
    while(itCoor.HaySiguiente()){
        if(itCoor.Siguiente() != p){
            Lista<InfoPokemon>::Iterador itPokemon = _posicionesPokemons.significado(itCoor.Siguiente());
            ActualizarPokemon(itPokemon);
        }
        itCoor.Avanzar();
    }
}

Dicc<Pokemon, Nat> Juego::pokemons(const Jugador &j) const {
    InfoJugador jugador = _jugadoresPorID[j].info.Siguiente();
    Lista<Lista<InfoPokemon>::Iterador>::Iterador it = jugador.pokemonesCapturados.CrearIt();
    Dicc<Pokemon, Nat> dicc;
    while(it.HaySiguiente()){
        Pokemon tipo = it.Siguiente().Siguiente().tipo;
        if (!dicc.Definido(tipo)){
            dicc.DefinirRapido(tipo, 1);
        }else{
            Nat cantidad = dicc.Significado(tipo);
            dicc.Definir(tipo, cantidad + 1);
        }
        it.Avanzar();
    }
    return dicc;
}