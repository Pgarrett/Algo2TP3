#include <iostream>
#include "../mini_test.h"
#include "../modulos/diccString.h"
#include "TestsDiccString.h"


void TestsDiccString::correr_tests() {
//    RUN_TEST(test_diccstring_claves_dicc_vacio);
    RUN_TEST(test_diccstring_definir_definido);
    RUN_TEST(test_diccstring_obtener);
    RUN_TEST(test_diccstring_borrar);
    //Realizar más test para chequear el funcionamiento del diccionario sobre trie.
    RUN_TEST(test_diccstring_raro);
    RUN_TEST(test_diccstring_repetidos);
    RUN_TEST(test_diccstring_violento);
    RUN_TEST(test_diccstring_check_trie_prefix);
    RUN_TEST(test_diccstring_check_trie);
    RUN_TEST(test_diccstring_check_trie_const);
}

//Chequea que el diccionario vacio no tenga claves
/*void TestsDiccString::test_diccstring_claves_dicc_vacio() {
    DiccString<int> d;
    ASSERT(d.Claves().cardinal() == 0);
}*/


//Chequea el definir y definido
void TestsDiccString::test_diccstring_definir_definido() {
    DiccString<int> d;
    d.Definir("hola", 42);
    ASSERT(d.Definido("hola"));
    ASSERT(!d.Definido("casona"));
    ASSERT(!d.Definido("casa"));
    d.Definir("casona", 13);

    ASSERT(d.Definido("hola"));
    ASSERT(d.Definido("casona"));
    ASSERT(!d.Definido("casa"));

    d.Definir("casa", 6);
    ASSERT(d.Definido("hola"));
    ASSERT(d.Definido("casona"));
    ASSERT(d.Definido("casa"));
}


//cheque el obtener
void TestsDiccString::test_diccstring_obtener() {
    DiccString<int> d;
    d.Definir("hola", 42);
    d.Definir("casa", 22);

    ASSERT(d.Significado("hola") == 42);
    ASSERT(d.Significado("casa") == 22);

    DiccString<int> e;
    e.Definir("amend", 10);
    ASSERT(e.Significado("amend") == 10);
}


//cheque el borrar
void TestsDiccString::test_diccstring_borrar() {
    //Completar este test para:
    //Verificar que al borrar una palabra, esta deja de estar definida en el diccionario
    //Chequear que si dos palabras comparten prefijos y una de ellas se borrar, la otra debe seguir estando definida
    //Analizar que el borrado funciona bien si el diccionario tiene definido una sola palabra y esta se borra.

    DiccString<int> d;
    d.Definir("hola", 42);
    d.Definir("casa", 22);
    d.Borrar("casa");
    ASSERT(d.Definido("hola"));
    ASSERT(!d.Definido("casa"));


    DiccString<int> a;
    a.Definir("amend", 10);
    a.Borrar("amend");
    ASSERT(!a.Definido("amend"));

    DiccString<int> b;
    b.Definir("amend", 10);
    b.Definir("amen", 9);
    b.Borrar("amend");
    ASSERT(!b.Definido("amend"));
    ASSERT(b.Definido("amen"));

    DiccString<int> c;
    c.Definir("amend", 10);
    c.Definir("amen", 9);
    c.Borrar("amen");
    ASSERT(c.Definido("amend"));
    ASSERT(!c.Definido("amen"));


    DiccString<int> e;
    e.Definir("amend", 10);
    e.Borrar("amend");
    ASSERT(!e.Definido("amend"));

    DiccString<int> f;
    f.Definir("amend", 10);
    f.Definir("america", 9);
    f.Borrar("amend");
    ASSERT(!f.Definido("amend"));
    ASSERT(f.Definido("america"));

}

void TestsDiccString::test_diccstring_raro() {
    DiccString<int> e;
    e.Definir("amend", 10);
    DiccString<int> d = DiccString<int>(e);
    ASSERT(d.Definido("amend"));
}

void TestsDiccString::test_diccstring_repetidos() {
    DiccString<int> f;
    int i = 0;

    f.Definir("spicy", i++);
    f.Definir("spicy", i++);
    f.Definir("spicy", i++);
    f.Definir("spicy", i++);
    f.Definir("spicy", i++);
    f.Definir("spicy", i++);
    f.Definir("spicy", i++);
    f.Definir("spicy", i++);
    f.Definir("spicy", i++);
    f.Definir("spicy", i++);
    f.Definir("spicy", i++);
    f.Definir("spicy", i++);
    f.Definir("spicy", i++);
    f.Definir("spicy", i++);
    f.Definir("spicy", i++);
    f.Definir("spicy", i++);
    f.Definir("spicy", i++);
}

void TestsDiccString::test_diccstring_violento() {
    DiccString<int> a;
    int i = 0;


    a.Definir("abbey", i++);
    a.Definir("favourite", i++);
    a.Definir("make", i++);
    a.Definir("condition", i++);
    a.Definir("seek", i++);
    a.Definir("official", i++);
    a.Definir("wander", i++);
    a.Definir("dorm", i++);
    a.Definir("funeral", i++);
    a.Definir("compliance", i++);
    a.Definir("manual", i++);
    a.Definir("favour", i++);
    a.Definir("illustrate", i++);
    a.Definir("producer", i++);
    a.Definir("braid", i++);
    a.Definir("easy", i++);
    a.Definir("palace", i++);
    a.Definir("chalk", i++);
    a.Definir("disappear", i++);
    a.Definir("population", i++);
    a.Definir("fate", i++);
    a.Definir("sunshine", i++);
    a.Definir("conclusion", i++);
    a.Definir("tendency", i++);
    a.Definir("junior", i++);
    a.Definir("contrary", i++);
    a.Definir("answer", i++);
    a.Definir("suspect", i++);
    a.Definir("accompany", i++);
    a.Definir("cabin", i++);
    a.Definir("mood", i++);
    a.Definir("tournament", i++);
    a.Definir("trustee", i++);
    a.Definir("solo", i++);
    a.Definir("hay", i++);
    a.Definir("gradient", i++);
    a.Definir("complain", i++);
    a.Definir("teacher", i++);
    a.Definir("spend", i++);
    a.Definir("discover", i++);
    a.Definir("classroom", i++);
    a.Definir("flavor", i++);
    a.Definir("available", i++);
    a.Definir("doll", i++);
    a.Definir("lot", i++);
    a.Definir("fruit", i++);
    a.Definir("packet", i++);
    a.Definir("neck", i++);
    a.Definir("strikebreaker", i++);
    a.Definir("witness", i++);
    a.Definir("distinct", i++);
    a.Definir("look", i++);
    a.Definir("bland", i++);
    a.Definir("represent", i++);
    a.Definir("kid", i++);
    a.Definir("amber", i++);
    a.Definir("asset", i++);
    a.Definir("horse", i++);
    a.Definir("opinion", i++);
    a.Definir("suite", i++);
    a.Definir("pig", i++);
    a.Definir("horn", i++);
    a.Definir("rugby", i++);
    a.Definir("penetrate", i++);
    a.Definir("efflux", i++);
    a.Definir("pray", i++);
    a.Definir("conversation", i++);
    a.Definir("applaud", i++);
    a.Definir("skate", i++);
    a.Definir("feminist", i++);
    a.Definir("tongue", i++);
    a.Definir("behave", i++);
    a.Definir("lift", i++);
    a.Definir("occasion", i++);
    a.Definir("seller", i++);
    a.Definir("crop", i++);
    a.Definir("node", i++);
    a.Definir("wife", i++);
    a.Definir("warrant", i++);
    a.Definir("systematic", i++);
    a.Definir("escape", i++);
    a.Definir("train", i++);
    a.Definir("city", i++);
    a.Definir("meaning", i++);
    a.Definir("breast", i++);
    a.Definir("accumulation", i++);
    a.Definir("employee", i++);
    a.Definir("overall", i++);
    a.Definir("real", i++);
    a.Definir("abortion", i++);
    a.Definir("shave", i++);
    a.Definir("leftovers", i++);
    a.Definir("include", i++);
    a.Definir("buy", i++);
    a.Definir("grimace", i++);
    a.Definir("golf", i++);
    a.Definir("simplicity", i++);
    a.Definir("inquiry", i++);
    a.Definir("incapable", i++);
    a.Definir("old", i++);
    a.Definir("root", i++);
    a.Definir("hot", i++);
    a.Definir("training", i++);
    a.Definir("engagement", i++);
    a.Definir("gradual", i++);
    a.Definir("tone", i++);
    a.Definir("pottery", i++);
    a.Definir("provide", i++);
    a.Definir("innovation", i++);
    a.Definir("bomb", i++);
    a.Definir("nose", i++);
    a.Definir("essential", i++);
    a.Definir("punch", i++);
    a.Definir("will", i++);
    a.Definir("similar", i++);
    a.Definir("bend", i++);
    a.Definir("opposition", i++);
    a.Definir("factor", i++);
    a.Definir("owner", i++);
    a.Definir("past", i++);
    a.Definir("instinct", i++);
    a.Definir("notebook", i++);
    a.Definir("mail carrier", i++);
    a.Definir("decoration", i++);
    a.Definir("excavate", i++);
    a.Definir("mouse", i++);
    a.Definir("crouch", i++);
    a.Definir("premium", i++);
    a.Definir("clinic", i++);
    a.Definir("elect", i++);
    a.Definir("minimum", i++);
    a.Definir("indication", i++);
    a.Definir("deficiency", i++);
    a.Definir("dull", i++);
    a.Definir("approach", i++);
    a.Definir("avenue", i++);
    a.Definir("zone", i++);
    a.Definir("outlook", i++);
    a.Definir("glue", i++);
    a.Definir("break in", i++);
    a.Definir("expenditure", i++);
    a.Definir("pest", i++);
    a.Definir("soldier", i++);
    a.Definir("exception", i++);
    a.Definir("inject", i++);
    a.Definir("manage", i++);
    a.Definir("wagon", i++);
    a.Definir("hike", i++);
    a.Definir("translate", i++);
    a.Definir("action", i++);
    a.Definir("agony", i++);
    a.Definir("exhibition", i++);
    a.Definir("state", i++);
    a.Definir("sentiment", i++);
    a.Definir("ceremony", i++);
    a.Definir("inhabitant", i++);
    a.Definir("solution", i++);
    a.Definir("carpet", i++);
    a.Definir("costume", i++);
    a.Definir("end", i++);
    a.Definir("please", i++);
    a.Definir("ribbon", i++);
    a.Definir("defeat", i++);
    a.Definir("country", i++);
    a.Definir("hope", i++);
    a.Definir("impress", i++);
    a.Definir("situation", i++);
    a.Definir("cane", i++);
    a.Definir("happen", i++);
    a.Definir("square", i++);
    a.Definir("blade", i++);
    a.Definir("illness", i++);
    a.Definir("freighter", i++);
    a.Definir("asylum", i++);
    a.Definir("salt", i++);
    a.Definir("progressive", i++);
    a.Definir("transaction", i++);
    a.Definir("coffee", i++);
    a.Definir("shareholder", i++);
    a.Definir("suit", i++);
    a.Definir("umbrella", i++);
    a.Definir("tribute", i++);
    a.Definir("sigh", i++);
    a.Definir("due", i++);
    a.Definir("hurl", i++);
    a.Definir("burial", i++);
    a.Definir("quote", i++);
    a.Definir("ample", i++);
    a.Definir("rough", i++);
    a.Definir("normal", i++);
    a.Definir("prey", i++);
    a.Definir("walk", i++);
    a.Definir("color-blind", i++);
    a.Definir("broken", i++);
    a.Definir("energy", i++);
    a.Definir("vigorous", i++);
    a.Definir("team", i++);
    a.Definir("tax", i++);
    a.Definir("information", i++);
    a.Definir("emergency", i++);


    DiccString<int> b = DiccString<int>(a);


    a.Borrar("abbey");
    a.Borrar("favourite");
    a.Borrar("make");
    a.Borrar("condition");
    a.Borrar("seek");
    a.Borrar("official");
    a.Borrar("wander");
    a.Borrar("dorm");
    a.Borrar("funeral");
    a.Borrar("compliance");
    a.Borrar("manual");
    a.Borrar("favour");
    a.Borrar("illustrate");
    a.Borrar("producer");
    a.Borrar("braid");
    a.Borrar("easy");
    a.Borrar("palace");
    a.Borrar("chalk");
    a.Borrar("disappear");
    a.Borrar("population");
    a.Borrar("fate");
    a.Borrar("sunshine");
    a.Borrar("conclusion");
    a.Borrar("tendency");
    a.Borrar("junior");
    a.Borrar("contrary");
    a.Borrar("answer");
    a.Borrar("suspect");
    a.Borrar("accompany");
    a.Borrar("cabin");
    a.Borrar("mood");
    a.Borrar("tournament");
    a.Borrar("trustee");
    a.Borrar("solo");
    a.Borrar("hay");
    a.Borrar("gradient");
    a.Borrar("complain");
    a.Borrar("teacher");
    a.Borrar("spend");
    a.Borrar("discover");
    a.Borrar("classroom");
    a.Borrar("flavor");
    a.Borrar("available");
    a.Borrar("doll");
    a.Borrar("lot");
    a.Borrar("fruit");
    a.Borrar("packet");
    a.Borrar("neck");
    a.Borrar("strikebreaker");
    a.Borrar("witness");
    a.Borrar("distinct");
    a.Borrar("look");
    a.Borrar("bland");
    a.Borrar("represent");
    a.Borrar("kid");
    a.Borrar("amber");
    a.Borrar("asset");
    a.Borrar("horse");
    a.Borrar("opinion");
    a.Borrar("suite");
    a.Borrar("pig");
    a.Borrar("horn");
    a.Borrar("rugby");
    a.Borrar("penetrate");
    a.Borrar("efflux");
    a.Borrar("pray");
    a.Borrar("conversation");
    a.Borrar("applaud");
    a.Borrar("skate");
    a.Borrar("feminist");
    a.Borrar("tongue");
    a.Borrar("behave");
    a.Borrar("lift");
    a.Borrar("occasion");
    a.Borrar("seller");
    a.Borrar("crop");
    a.Borrar("node");
    a.Borrar("wife");
    a.Borrar("warrant");
    a.Borrar("systematic");
    a.Borrar("escape");
    a.Borrar("train");
    a.Borrar("city");
    a.Borrar("meaning");
    a.Borrar("breast");
    a.Borrar("accumulation");
    a.Borrar("employee");
    a.Borrar("overall");
    a.Borrar("real");
    a.Borrar("abortion");
    a.Borrar("shave");
    a.Borrar("leftovers");
    a.Borrar("include");
    a.Borrar("buy");
    a.Borrar("grimace");
    a.Borrar("golf");
    a.Borrar("simplicity");
    a.Borrar("inquiry");
    a.Borrar("incapable");
    a.Borrar("old");
    a.Borrar("root");
    a.Borrar("hot");
    a.Borrar("training");
    a.Borrar("engagement");
    a.Borrar("gradual");
    a.Borrar("tone");
    a.Borrar("pottery");
    a.Borrar("provide");
    a.Borrar("innovation");
    a.Borrar("bomb");
    a.Borrar("nose");
    a.Borrar("essential");
    a.Borrar("punch");
    a.Borrar("will");
    a.Borrar("similar");
    a.Borrar("bend");
    a.Borrar("opposition");
    a.Borrar("factor");
    a.Borrar("owner");
    a.Borrar("past");
    a.Borrar("instinct");
    a.Borrar("notebook");
    a.Borrar("mail carrier");
    a.Borrar("decoration");
    a.Borrar("excavate");
    a.Borrar("mouse");
    a.Borrar("crouch");
    a.Borrar("premium");
    a.Borrar("clinic");
    a.Borrar("elect");
    a.Borrar("minimum");
    a.Borrar("indication");
    a.Borrar("deficiency");
    a.Borrar("dull");
    a.Borrar("approach");
    a.Borrar("avenue");
    a.Borrar("zone");
    a.Borrar("outlook");
    a.Borrar("glue");
    a.Borrar("break in");
    a.Borrar("expenditure");
    a.Borrar("pest");
    a.Borrar("soldier");
    a.Borrar("exception");
    a.Borrar("inject");
    a.Borrar("manage");
    a.Borrar("wagon");
    a.Borrar("hike");
    a.Borrar("translate");
    a.Borrar("action");
    a.Borrar("agony");
    a.Borrar("exhibition");
    a.Borrar("state");
    a.Borrar("sentiment");
    a.Borrar("ceremony");
    a.Borrar("inhabitant");
    a.Borrar("solution");
    a.Borrar("carpet");
    a.Borrar("costume");
    a.Borrar("end");
    a.Borrar("please");
    a.Borrar("ribbon");
    a.Borrar("defeat");
    a.Borrar("country");
    a.Borrar("hope");
    a.Borrar("impress");
    a.Borrar("situation");
    a.Borrar("cane");
    a.Borrar("happen");
    a.Borrar("square");
    a.Borrar("blade");
    a.Borrar("illness");
    a.Borrar("freighter");
    a.Borrar("asylum");
    a.Borrar("salt");
    a.Borrar("progressive");
    a.Borrar("transaction");
    a.Borrar("coffee");
    a.Borrar("shareholder");
    a.Borrar("suit");
    a.Borrar("umbrella");
    a.Borrar("tribute");
    a.Borrar("sigh");
    a.Borrar("due");
    a.Borrar("hurl");
    a.Borrar("burial");
    a.Borrar("quote");
    a.Borrar("ample");
    a.Borrar("rough");
    a.Borrar("normal");
    a.Borrar("prey");
    a.Borrar("walk");
    a.Borrar("color-blind");
    a.Borrar("broken");
    a.Borrar("energy");
    a.Borrar("vigorous");
    a.Borrar("team");
    a.Borrar("tax");
    a.Borrar("information");
    a.Borrar("emergency");


    b.Borrar("abbey");
    b.Borrar("favourite");
    b.Borrar("make");
    b.Borrar("condition");
    b.Borrar("seek");
    b.Borrar("official");
    b.Borrar("wander");
    b.Borrar("dorm");
    b.Borrar("funeral");
    b.Borrar("compliance");
    b.Borrar("manual");
    b.Borrar("favour");
    b.Borrar("illustrate");
    b.Borrar("producer");
    b.Borrar("braid");
    b.Borrar("easy");
    b.Borrar("palace");
    b.Borrar("chalk");
    b.Borrar("disappear");
    b.Borrar("population");
    b.Borrar("fate");
    b.Borrar("sunshine");
    b.Borrar("conclusion");
    b.Borrar("tendency");
    b.Borrar("junior");
    b.Borrar("contrary");
    b.Borrar("answer");
    b.Borrar("suspect");
    b.Borrar("accompany");
    b.Borrar("cabin");
    b.Borrar("mood");
    b.Borrar("tournament");
    b.Borrar("trustee");
    b.Borrar("solo");
    b.Borrar("hay");
    b.Borrar("gradient");
    b.Borrar("complain");
    b.Borrar("teacher");
    b.Borrar("spend");
    b.Borrar("discover");
    b.Borrar("classroom");
    b.Borrar("flavor");
    b.Borrar("available");
    b.Borrar("doll");
    b.Borrar("lot");
    b.Borrar("fruit");
    b.Borrar("packet");
    b.Borrar("neck");
    b.Borrar("strikebreaker");
    b.Borrar("witness");
    b.Borrar("distinct");
    b.Borrar("look");
    b.Borrar("bland");
    b.Borrar("represent");
    b.Borrar("kid");
    b.Borrar("amber");
    b.Borrar("asset");
    b.Borrar("horse");
    b.Borrar("opinion");
    b.Borrar("suite");
    b.Borrar("pig");
    b.Borrar("horn");
    b.Borrar("rugby");
    b.Borrar("penetrate");
    b.Borrar("efflux");
    b.Borrar("pray");
    b.Borrar("conversation");
    b.Borrar("applaud");
    b.Borrar("skate");
    b.Borrar("feminist");
    b.Borrar("tongue");
    b.Borrar("behave");
    b.Borrar("lift");
    b.Borrar("occasion");
    b.Borrar("seller");
    b.Borrar("crop");
    b.Borrar("node");
    b.Borrar("wife");
    b.Borrar("warrant");
    b.Borrar("systematic");
    b.Borrar("escape");
    b.Borrar("train");
    b.Borrar("city");
    b.Borrar("meaning");
    b.Borrar("breast");
    b.Borrar("accumulation");
    b.Borrar("employee");
    b.Borrar("overall");
    b.Borrar("real");
    b.Borrar("abortion");
    b.Borrar("shave");
    b.Borrar("leftovers");
    b.Borrar("include");
    b.Borrar("buy");
    b.Borrar("grimace");
    b.Borrar("golf");
    b.Borrar("simplicity");
    b.Borrar("inquiry");
    b.Borrar("incapable");
    b.Borrar("old");
    b.Borrar("root");
    b.Borrar("hot");
    b.Borrar("training");
    b.Borrar("engagement");
    b.Borrar("gradual");
    b.Borrar("tone");
    b.Borrar("pottery");
    b.Borrar("provide");
    b.Borrar("innovation");
    b.Borrar("bomb");
    b.Borrar("nose");
    b.Borrar("essential");
    b.Borrar("punch");
    b.Borrar("will");
    b.Borrar("similar");
    b.Borrar("bend");
    b.Borrar("opposition");
    b.Borrar("factor");
    b.Borrar("owner");
    b.Borrar("past");
    b.Borrar("instinct");
    b.Borrar("notebook");
    b.Borrar("mail carrier");
    b.Borrar("decoration");
    b.Borrar("excavate");
    b.Borrar("mouse");
    b.Borrar("crouch");
    b.Borrar("premium");
    b.Borrar("clinic");
    b.Borrar("elect");
    b.Borrar("minimum");
    b.Borrar("indication");
    b.Borrar("deficiency");
    b.Borrar("dull");
    b.Borrar("approach");
    b.Borrar("avenue");
    b.Borrar("zone");
    b.Borrar("outlook");
    b.Borrar("glue");
    b.Borrar("break in");
    b.Borrar("expenditure");
    b.Borrar("pest");
    b.Borrar("soldier");
    b.Borrar("exception");
    b.Borrar("inject");
    b.Borrar("manage");
    b.Borrar("wagon");
    b.Borrar("hike");
    b.Borrar("translate");
    b.Borrar("action");
    b.Borrar("agony");
    b.Borrar("exhibition");
    b.Borrar("state");
    b.Borrar("sentiment");
    b.Borrar("ceremony");
    b.Borrar("inhabitant");
    b.Borrar("solution");
    b.Borrar("carpet");
    b.Borrar("costume");
    b.Borrar("end");
    b.Borrar("please");
    b.Borrar("ribbon");
    b.Borrar("defeat");
    b.Borrar("country");
    b.Borrar("hope");
    b.Borrar("impress");
    b.Borrar("situation");
    b.Borrar("cane");
    b.Borrar("happen");
    b.Borrar("square");
    b.Borrar("blade");
    b.Borrar("illness");
    b.Borrar("freighter");
    b.Borrar("asylum");
    b.Borrar("salt");
    b.Borrar("progressive");
    b.Borrar("transaction");
    b.Borrar("coffee");
    b.Borrar("shareholder");
    b.Borrar("suit");
    b.Borrar("umbrella");
    b.Borrar("tribute");
    b.Borrar("sigh");
    b.Borrar("due");
    b.Borrar("hurl");
    b.Borrar("burial");
    b.Borrar("quote");
    b.Borrar("ample");
    b.Borrar("rough");
    b.Borrar("normal");
    b.Borrar("prey");
    b.Borrar("walk");
    b.Borrar("color-blind");
    b.Borrar("broken");
    b.Borrar("energy");
    b.Borrar("vigorous");
    b.Borrar("team");
    b.Borrar("tax");
    b.Borrar("information");
    b.Borrar("emergency");

}

void TestsDiccString::test_diccstring_check_trie() {
    DiccString<int> trai;
    trai.Definir("uno", 1);
    trai.Definir("dos", 2);
    trai.Definir("tres", 3);
    trai.Definir("cuatro", 4);

    ASSERT(trai.Definido("uno"));
    ASSERT_EQ(trai.Significado("dos"), 2);
    ASSERT(trai.Definido("tres"));
    ASSERT_EQ(trai.Significado("cuatro"), 4);

    trai.Borrar("uno");
    ASSERT(!trai.Definido("uno"));

}

void TestsDiccString::test_diccstring_check_trie_prefix() {
    DiccString<int> d;

    d.Definir("a", 0);
    d.Definir("ab", 1);
    d.Definir("abc", 2);
    d.Definir("abcd", 3);
    d.Definir("abcde", 4);

    ASSERT_EQ(d.Significado("a"), 0);
    ASSERT_EQ(d.Significado("ab"), 1);
    ASSERT_EQ(d.Significado("abc"), 2);
    ASSERT_EQ(d.Significado("abcd"), 3);
    ASSERT_EQ(d.Significado("abcde"), 4);
}

void TestsDiccString::test_diccstring_check_trie_const() {
    DiccString<int> d;
    d.Definir("a", 0);
    d.Definir("ab", 1);
    d.Definir("abc", 2);

    const DiccString<int> constDicc(d);

    ASSERT_EQ(constDicc.Significado("a"), 0);
    ASSERT_EQ(constDicc.Significado("ab"), 1);
    ASSERT_EQ(constDicc.Significado("abc"), 2);
}
