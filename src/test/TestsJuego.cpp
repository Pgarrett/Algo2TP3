#include "TestsJuego.h"
#include "../mini_test.h"
#include "../modulos/Juego.h"

typedef Coordenada Coor;

Mapa crearMapaDefault();

void TestsJuego::correr_tests() {
    // CrearJuego
    RUN_TEST(test_juego_constructor_con_mapa);
    RUN_TEST(test_juego_crear_juego_sin_jugadores);
    RUN_TEST(test_juego_crear_juego_sin_expulsados);
    RUN_TEST(test_juego_crear_juego_sin_posiciones_con_pokemons);

    // AgregarJugador
    RUN_TEST(test_juego_jugadores_con_id_secuencial);
    RUN_TEST(test_juego_jugador_nuevo_no_modifica_expulsados);
    RUN_TEST(test_juego_jugador_nuevo_desconectado);
    RUN_TEST(test_juego_jugador_nuevo_sin_sanciones);

    // Hay pokemons cercano
    RUN_TEST(test_juego_hay_pokemon_cercano_coordenada_invalida);
    RUN_TEST(test_juego_hay_pokemon_cercano_coordenada_con_pokemon);
    RUN_TEST(test_juego_hay_pokemon_cercano_coordenada_con_pokemon_cercano);
    RUN_TEST(test_juego_hay_pokemon_cercano_coordenada_con_pokemon_lejano);

    // conectarse
    RUN_TEST(test_juego_conectarse_conecta_al_jugador)
    RUN_TEST(test_juego_conectarse_pone_al_jugador_en_posicion)

    // entrenadores posibles
    RUN_TEST(test_juego_entrenadores_posibles_ningun_entrenador)
    RUN_TEST(test_juego_entrenadores_posibles_entrenador_cercano)
    RUN_TEST(test_juego_entrenadores_posibles_entrenador_lejano)
//    RUN_TEST(test_juego_entrenadores_posibles_jugador_se_desconecta)
    RUN_TEST(test_juego_entrenadores_posibles_pokemon_se_agrega_despues)

    // pos pokemon cercano
    RUN_TEST(test_juego_pos_pokemon_cercano_coordenada_con_pokemon);
    RUN_TEST(test_juego_pos_pokemon_cercano_coordenada_con_pokemon_cercano);

    // desconectarse
    RUN_TEST(test_juego_desconectarse_desconecta_al_jugador);
    RUN_TEST(test_juego_desconectarse_borra_jugador_de_posiciones_jugadores);
    RUN_TEST(test_juego_desconectarse_no_cambia_sanciones_del_jugador_sin_sanciones);

    // cantPokemonsTotales
    RUN_TEST(test_juego_cant_pokemones_totales_nuevo_juego_igual_a_cero);
    RUN_TEST(test_juego_cant_pokemones_totales_agregando_pokemon_igual_a_uno);

}

Mapa crearMapaDefault() {
    Mapa mapa;
    mapa.agregarCoordenada(Coor(0, 0));
    mapa.agregarCoordenada(Coor(0, 1));
    mapa.agregarCoordenada(Coor(0, 2));
    mapa.agregarCoordenada(Coor(1, 2));
    mapa.agregarCoordenada(Coor(10, 0));
    mapa.agregarCoordenada(Coor(1, 4));
    return mapa;
}

// CrearJuego

void TestsJuego::test_juego_constructor_con_mapa() {
    Mapa mapa = crearMapaDefault();

    Juego j(mapa);

    ASSERT(j.mapa().coordenadas() == mapa.coordenadas());
}

void TestsJuego::test_juego_crear_juego_sin_jugadores() {
    Mapa mapa = crearMapaDefault();

    Juego j(mapa);

    ASSERT(j.jugadores().Cardinal() == 0);
}

void TestsJuego::test_juego_jugadores_con_id_secuencial() {
    Mapa mapa = crearMapaDefault();

    Juego j(mapa);
    ASSERT(j.agregarJugador() == 0);
    ASSERT(j.agregarJugador() == 1);
}

void TestsJuego::test_juego_crear_juego_sin_expulsados() {
    Mapa mapa = crearMapaDefault();
    Juego j(mapa);

    ASSERT(j.expulsados().Cardinal() == 0);
}

void TestsJuego::test_juego_crear_juego_sin_posiciones_con_pokemons() {
    Mapa mapa = crearMapaDefault();
    Juego j(mapa);
    ASSERT(j.posConPokemons().Cardinal() == 0);
}

void TestsJuego::test_juego_crear_juego_sin_posiciones_con_jugadores() {
    ASSERT(true);
}

// AgregarJugador
void TestsJuego::test_juego_jugador_nuevo_no_modifica_expulsados() {
    Mapa mapa = crearMapaDefault();

    Juego j(mapa);

    ASSERT(j.expulsados().Cardinal() == 0);
    j.agregarJugador();
    ASSERT(j.expulsados().Cardinal() == 0);
}

void TestsJuego::test_juego_jugador_nuevo_desconectado() {
    Mapa mapa = crearMapaDefault();
    Juego j(mapa);

    Jugador jug = j.agregarJugador();

    ASSERT(not j.estaConectado(jug));
}

void TestsJuego::test_juego_jugador_nuevo_sin_sanciones() {
    Mapa mapa = crearMapaDefault();
    Juego j(mapa);

    Jugador jug = j.agregarJugador();

    ASSERT(j.sanciones(jug) == 0);
}

void TestsJuego::test_juego_jugador_nuevo_sin_pokemones() {
    /* TODO revisar con leticia, la implementacion pide que pokemons devuelva un dicc<pokemon, nat>
    * TODO nosotros no hacemos eso (porque la cagamos cuando diseñanmos)
    */
    Mapa mapa = crearMapaDefault();
    Juego j(mapa);

    Jugador jug = j.agregarJugador();

    ASSERT(j.sanciones(jug) == 0);
}

// Conectarse


// HayPokemonCercano
void TestsJuego::test_juego_hay_pokemon_cercano_coordenada_invalida() {
    Mapa mapa = crearMapaDefault();

    Juego j(mapa);

    ASSERT(not j.hayPokemonCercano(Coor(1, 1)));
}

void TestsJuego::test_juego_hay_pokemon_cercano_coordenada_con_pokemon() {
    Mapa mapa = crearMapaDefault();
    Juego j(mapa);

    j.agregarPokemon("poke", Coor(1, 2));

    ASSERT(j.hayPokemonCercano(Coor(1, 2)));
}

void TestsJuego::test_juego_hay_pokemon_cercano_coordenada_con_pokemon_cercano() {
    Mapa mapa = crearMapaDefault();
    Juego j(mapa);

    j.agregarPokemon("poke", Coor(1, 2));

    ASSERT(j.hayPokemonCercano(Coor(1, 1)));
}

void TestsJuego::test_juego_hay_pokemon_cercano_coordenada_con_pokemon_lejano() {
    Mapa mapa = crearMapaDefault();
    Juego j(mapa);

    j.agregarPokemon("poke", Coor(2, 2));

    ASSERT(not j.hayPokemonCercano(Coor(0, 0)));
}

void TestsJuego::test_juego_conectarse_conecta_al_jugador() {
    Mapa mapa = crearMapaDefault();
    Juego j(mapa);
    Nat id = j.agregarJugador();

    j.conectarse(id, Coor(0, 0));

    ASSERT(j.estaConectado(id))
}

void TestsJuego::test_juego_conectarse_pone_al_jugador_en_posicion() {
    Mapa mapa = crearMapaDefault();
    Juego j(mapa);
    Nat id = j.agregarJugador();

    j.conectarse(id, Coor(1, 2));

    ASSERT(j.posicion(id) == Coor(1, 2))
}

void TestsJuego::test_juego_entrenadores_posibles_ningun_entrenador() {
    Juego j(crearMapaDefault());
    j.agregarJugador();
    j.agregarPokemon("poke", Coor(0, 0));

    Conj<Jugador> posibles = j.entrenadoresPosibles(Coor(0, 0));

    ASSERT(posibles.EsVacio())
}

// Un entrenador cerca del pokemon deberia ser un entrenador posible
void TestsJuego::test_juego_entrenadores_posibles_entrenador_cercano() {
    Juego j(crearMapaDefault());
    Jugador jugador = j.agregarJugador();
    j.agregarPokemon("poke", Coor(0, 2));
    j.conectarse(jugador, Coor(1, 2));

    Conj<Jugador> posibles = j.entrenadoresPosibles(Coor(0, 2));

    ASSERT(posibles.Cardinal() == 1)
    ASSERT(posibles.Pertenece(jugador))
}

// Un entrenador lejos del pokemon no deberia ser un entrenador posible
void TestsJuego::test_juego_entrenadores_posibles_entrenador_lejano() {
    Juego j(crearMapaDefault());
    Jugador jugador = j.agregarJugador();
    j.agregarPokemon("poke", Coor(0, 0));
    j.conectarse(jugador, Coor(10, 0));

    Conj<Jugador> posibles = j.entrenadoresPosibles(Coor(0, 0));

    ASSERT(posibles.EsVacio())
}

// Un jugador que se desconecta no deberia ser un entrenador posible
void TestsJuego::test_juego_entrenadores_posibles_jugador_se_desconecta() {
    Juego j(crearMapaDefault());
    Jugador jugador = j.agregarJugador();
    j.agregarPokemon("poke", Coor(0, 2));
    j.conectarse(jugador, Coor(1, 2));
    j.desconectarse(jugador);

    Conj<Jugador> posibles = j.entrenadoresPosibles(Coor(0, 2));

    ASSERT(posibles.EsVacio())
}

// Un jugador deberia ser un entrenador posible si un pokemon se agrega cerca de donde esta
void TestsJuego::test_juego_entrenadores_posibles_pokemon_se_agrega_despues() {
    Juego j(crearMapaDefault());
    Jugador jugador = j.agregarJugador();
    j.conectarse(jugador, Coor(1, 2));
    j.agregarPokemon("poke", Coor(0, 2));

    Conj<Jugador> posibles = j.entrenadoresPosibles(Coor(0, 2));

    ASSERT(posibles.Cardinal() == 1)
    ASSERT(posibles.Pertenece(jugador))
}


void TestsJuego::test_juego_pos_pokemon_cercano_coordenada_con_pokemon() {
    Mapa mapa = crearMapaDefault();
    Juego j(mapa);

    j.agregarPokemon("poke", Coor(1, 2));

    ASSERT(j.posPokemonCercano(Coor(1, 2)) == Coor(1, 2));
}

void TestsJuego::test_juego_pos_pokemon_cercano_coordenada_con_pokemon_cercano() {
    Mapa mapa = crearMapaDefault();
    Juego j(mapa);

    j.agregarPokemon("poke", Coor(1, 2));

    ASSERT(j.posPokemonCercano(Coor(1, 1)) == Coor(1, 2));
}

void TestsJuego::test_juego_desconectarse_desconecta_al_jugador() {
    Mapa mapa = crearMapaDefault();
    Juego j(mapa);
    Jugador j1 = j.agregarJugador();
    j.conectarse(j1, Coor(0,2));
    j.desconectarse(j1);
    ASSERT(!j.estaConectado(j1));
}

void TestsJuego::test_juego_desconectarse_borra_jugador_de_posiciones_jugadores() {
    Mapa mapa = crearMapaDefault();
    Juego j(mapa);
    Jugador j1 = j.agregarJugador();
    j.conectarse(j1, Coor(0,2));
    ASSERT(j.jugadoresEnPos(Coor(0,2)).Siguiente() == 0);
    j.desconectarse(j1);
    ASSERT(!j.jugadoresEnPos(Coor(0,2)).HaySiguiente());
}

void TestsJuego::test_juego_desconectarse_no_cambia_sanciones_del_jugador_sin_sanciones() {
    Mapa mapa = crearMapaDefault();
    Juego j(mapa);
    Jugador j1 = j.agregarJugador();
    j.conectarse(j1, Coor(0,2));
    ASSERT(j.sanciones(j1) == 0);
    j.desconectarse(j1);
    ASSERT(j.sanciones(j1) == 0);
}

// cantPokemonsTotales

void TestsJuego::test_juego_cant_pokemones_totales_nuevo_juego_igual_a_cero() {
    Mapa mapa = crearMapaDefault();
    Juego j(mapa);
    ASSERT(j.cantPokemonsTotales() == 0);
}

void TestsJuego::test_juego_cant_pokemones_totales_agregando_pokemon_igual_a_uno() {
    Mapa mapa = crearMapaDefault();
    Juego j(mapa);
    j.agregarPokemon("pikachu", Coor(0,2));
    ASSERT(j.cantPokemonsTotales() == 1);
}
