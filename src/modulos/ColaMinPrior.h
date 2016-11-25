/*
Vacía() → res : colaMinPrior(α)
Pre ≡ {true}
Post ≡ {res = obs vacía}
Complejidad: O(1)
Descripción: Crea una cola de prioridad vacía
Vacía?(in c : colaMinPrior(α)) → res : bool
Pre ≡ {true}
Post ≡ {res = obs vacía?(c)}
Complejidad: O(1)
Descripción: Devuelve true si y sólo si la cola está vacía
Próximo(in c : colaMinPrior(α)) → res : α
Pre ≡ {¬vacía?(c)}
Post ≡ {alias(res = obs próximo(c))}
Complejidad: O(1)
Descripción: Devuelve el próximo elemento a desencolar
Aliasing: res es modificable si y sólo si c es modificable
Desencolar(in/out c : colaMinPrior(α))
Pre ≡ {¬vacía?(c) ∧ c = obs c 0 }
Post ≡ {c = obs desencolar(c 0 )}
Complejidad: O(log(tamaño(c)))
Descripción: Quita el elemento más prioritario
Encolar(in/out c : colaMinPrior(α), in p : nat, in a : α) → res : itColaMin(α)
Pre ≡ {c = obs c 0 }
Post ≡ {c = obs encolar(p,c 0 ) ∧ res = obs CrearIt(ColaASecu(c 0 ), a) ∧ alias(SecuSuby(res) = ColaASecu(c))}
Complejidad: O(log(|c|)) + copy(a)
Descripción: Agrega el elemento a de tipo α con prioridad p a la cola
Aliasing: Se agrega el elemento por copia
*/

#ifndef AED2_COLAMINPRIOR_H_
#define AED2_COLAMINPRIOR_H_

#include <ostream>
#include "../aed2/TiposBasicos.h"
#include "../aed2/Lista.h"
#include "../aed2/Arreglo.h"

using namespace aed2;
using namespace std;

template <typename T>
class ColaMinPrior
{
  public:
  // forward declarations
  // Las estructuras estan definidas mas abajo
  class Iterador;
  class const_Iterador;

  /// Crea una Cola Vacía. (Operación Vacia())
  ColaMinPrior();

  /// Crea por copia una cola (operación Copiar())
//  ColaMinPrior(const ColaMinPrior& otra);

  /// Destruye la Cola, incluyendo los T alojados
  ~ColaMinPrior();

  /// Operacion de asignacion
  //Lista<T>& operator=(const Lista<T>& otra);

  /// Opreaciones básicas
  bool EsVacia() const;
  Nat Tamano() const;

  /// Acceso al proximo (en O(1))
  /// Versiones modificables y no modificables
  T& Proximo();
  const T& Proximo() const;

  /// Operador "iésimo"
//  T& operator[](Nat i);
 // const T& operator[](Nat i) const;

  /// Elimina el elemento mas prioritario
  void Desencolar();
  /// Agrega un elemento en su posición correspondiente
  void Encolar(Nat prior, const T& elem);

  /// Inserción de elementos
  Iterador EliminarSiguiente();

  /// Creación del Iterador
  Iterador CrearIt();

  /// Creación del const_Iterador
  const_Iterador CrearIt() const;

	void mostrar(ostream&) const;

	friend ostream& operator<<(ostream& os, const ColaMinPrior<T> &c) {
		c.mostrar(os);
		return os;
	}

  /**********************************
   * Iterador de Lista, modificable *
   **********************************/
  class Iterador
  {
    public:

      Iterador();

      Iterador(const typename ColaMinPrior<T>::Iterador& otro);

      Iterador& operator = (const typename ColaMinPrior<T>::Iterador& otro);

      bool HaySiguiente() const;

      T& Siguiente();
      const T& Siguiente() const;

      void EliminarSiguiente();
      
      bool operator == (const typename ColaMinPrior<T>::Iterador& otro) const;
  private:

      ColaMinPrior<T>* _cola;

      typename ColaMinPrior<T>::Nodo* _nodo_siguiente;

      /// El constructor es privado, necesitamos el friend.
      Iterador(ColaMinPrior<T>* cola, typename ColaMinPrior<T>::Nodo* proximo);

      friend typename ColaMinPrior<T>::Iterador ColaMinPrior<T>::CrearIt();
      friend class ColaMinPrior<T>::const_Iterador;
  };

  /*******************************************
   * const_Iterador de ColaMinPrior, no modificable *
   *******************************************/
  class const_Iterador
  {
    public:

      const_Iterador();

      const_Iterador(const typename ColaMinPrior<T>::const_Iterador& otro);

      const_Iterador(const typename ColaMinPrior<T>::Iterador& otro);

      const_Iterador& operator = (const typename ColaMinPrior<T>::const_Iterador& otro);

      bool HaySiguiente() const;

      const T& Siguiente() const;

      bool operator == (const typename ColaMinPrior<T>::const_Iterador& otro) const;

  private:

      const ColaMinPrior<T>* _cola;

      const typename ColaMinPrior<T>::Nodo* _nodo_siguiente;

      /// El constructor es privado, necesitamos el friend.
      const_Iterador(const ColaMinPrior<T>* lista, const typename ColaMinPrior<T>::Nodo* proximo);

      friend typename ColaMinPrior<T>::const_Iterador ColaMinPrior<T>::CrearIt() const;
      friend typename ColaMinPrior<T>::const_Iterador ColaMinPrior<T>::CrearItUlt() const;

      //devuelve el nodo siguiente en la lista circular
      //const typename ColaMinPrior<T>::Nodo* SiguienteReal() const;
  };

private:

  struct Nodo
  {
    Nodo(const Nat p, const T& d) : prior(p), elem(d), padre(NULL), izq(NULL), der(NULL){};

    Nat prior;
    T elem;
    Nodo* padre;
    Nodo* izq;
    Nodo* der;

    void setPadre(Nodo* p){
		if (this != NULL){
			padre = p;
		}
	}
	
	void setIzq(Nodo* p){
		if (this != NULL){
			izq = p;
		}
	}

	void setDer(Nodo* p){
		if (this != NULL){
				der = p;	
		}
	}

	bool esRaiz(){
		return (padre == NULL);
	}

  };

	typename ColaMinPrior<T>::Nodo* UltimoNodo();
	Arreglo<int>* DecimalABinario(Nat);
	void swapCola(Nodo* p, Nodo* q);
	Nodo* padreNuevoNodo();
	void subir(Nodo* n);
	void mostrarNodo(std::ostream& os, Nodo* const p) const;
	bool checkNodos() const;
	bool checkNodo(typename ColaMinPrior<T>::Nodo* const p, bool izq) const;
 	Nodo* _proximo;
	Nat _tamano;
};

template<class T>
std::ostream& operator << (std::ostream& os, const ColaMinPrior<T>& l);

template<class T>
bool operator == (const ColaMinPrior<T>& l1, const ColaMinPrior<T>& k2);

  //  Implementacion de Lista

template <typename T>
ColaMinPrior<T>::ColaMinPrior()
  : _proximo(NULL), _tamano(0)
{}

/*template <typename T>
Lista<T>::Lista(const Lista<T>& otra)
  : primero_(NULL), longitud_(0)
{
  // TODO la idea es que haga shallow copy?
  // Pense que por convencon definiamos este operador con deep copy
  // de hecho el operador = hace deep copy
  *this = otra;
}*/
/*
template <typename T>
Lista<T>& Lista<T>::operator = (const Lista<T>& otra)
{
  // Limpio mi lista
  while( !EsVacia() ) {
    Desencolar();
  }

  // copio todos los elementos de la otra
  for(const_Iterador it = otra.CrearIt(); it.HaySiguiente(); it.Avanzar()) {
    this->AgregarAtras( it.Siguiente() );
  }

  return *this;
}*/

template <typename T>
ColaMinPrior<T>::~ColaMinPrior(){
  /*while(!EsVacia()) {
    Desencolar();
  }*/
}

template <typename T>
bool ColaMinPrior<T>::EsVacia() const{
  return _proximo == NULL;
}

template <typename T>
Nat ColaMinPrior<T>::Tamano() const{
  return _tamano;
}

template <typename T>
T& ColaMinPrior<T>::Proximo(){
  #ifdef DEBUG
  assert(!EsVacia());
  #endif

  return CrearIt().Siguiente();
}

template <typename T>
const T& ColaMinPrior<T>::Proximo() const{
  #ifdef DEBUG
  assert(!EsVacia());
  #endif

  return CrearIt().Siguiente();
}

/*
template <typename T>
T& Lista<T>::Ultimo(){
  #ifdef DEBUG
  assert( ! EsVacia() );
  #endif

  return CrearItUlt().Anterior();
}

template <typename T>
const T& Lista<T>::Ultimo() const
{
  #ifdef DEBUG
  assert( ! EsVacia() );
  #endif

  return CrearItUlt().Anterior();
}

template <typename T>
const T& Lista<T>::operator[](Nat i) const
{
  #ifdef DEBUG
  assert( i < longitud_ );
  #endif

  const_Iterador it = CrearIt();
  while( i > 0 ) {
    it.Avanzar();
    --i;
  }

  return it.Siguiente();
}

template <typename T>
T& Lista<T>::operator[](Nat i)
{
  #ifdef DEBUG
  assert( i < longitud_ );
  #endif

  Iterador it = CrearIt();
  while(i > 0)
  {
    it.Avanzar();
    --i;
  }

  return it.Siguiente();
}
*/
template <typename T>
void ColaMinPrior<T>::Desencolar(){
  	#ifdef DEBUG
  	assert(!EsVacia());
  	#endif
	Nodo* n = UltimoNodo();
	UltimoNodo();
}

template <typename T>
void ColaMinPrior<T>::Encolar(const Nat prior, const T& elem){
	Nodo* padre = padreNuevoNodo();
	Nodo* nuevo = new Nodo(prior,elem);
	if(_proximo == NULL){
		_proximo = nuevo;
		_proximo->padre = NULL;
	}else{
		if(padre->izq == NULL){
			padre->izq = nuevo;
		}else{
			padre->der = nuevo;
		}
		nuevo->padre = padre;
	}
	++_tamano;
  subir(nuevo);
}

template <typename T>
void ColaMinPrior<T>::subir(typename ColaMinPrior<T>::Nodo* n){
	bool swap = true;
	bool esRaiz = (n->padre == NULL);
	while (!esRaiz && swap){
		swap = false;
		if (n->prior < n->padre->prior){
		  swapCola(n->padre,n);
		  swap = true;
		}
		esRaiz = (n->padre == NULL);
	}
}

template <typename T>
typename ColaMinPrior<T>::Nodo* ColaMinPrior<T>::padreNuevoNodo(){
	Arreglo<int>* a = DecimalABinario(_tamano+1);
	Nodo* n = _proximo;
    for (int i = 1; i < a->Tamanho()-1; i++){
        if (a[0][i] == 0)
        	n = (n->izq);
        else
        	n = (n->der);
    }
    return(n);
}

template <typename T>
typename ColaMinPrior<T>::Nodo* ColaMinPrior<T>::UltimoNodo(){
    Arreglo<int>* a = DecimalABinario(_tamano);
    Nodo* n = _proximo;
    for (int i = 1; i < a->Tamanho(); i++){
        cout << a[0][i] << endl;
        if (a[0][i] == 0)
        	n = (n->izq);
        else
        	n = (n->der);
    }
    delete(a);
    return(n);
}

template <typename T>
Arreglo<int>* ColaMinPrior<T>::DecimalABinario(Nat d){
	Lista<int> temp;
	while(d > 0){
		temp.AgregarAdelante(d%2);
		d = (Nat)d/2;
	}
	Nat l = temp.Longitud();
 	Arreglo<int>* res = new Arreglo<int>(l);
	int i = 0;
	typename Lista<T>::Iterador it = temp.CrearIt();
	while(it.HaySiguiente() && i < temp.Longitud()){
		res->Definir(i, it.Siguiente());
		it.Avanzar();
		++i;
	}

	return(res);
}




template <typename T>
void ColaMinPrior<T>::swapCola(typename ColaMinPrior<T>::Nodo* p, typename ColaMinPrior<T>::Nodo* q){
/*	cout << endl << "ColaMinPrior" << endl;	 
	cout << "p_0 = " << p << " prior : " << p->prior << " elem : " << p->elem << endl;
	cout << " - - - - padre : " << p->padre << " izq : " << p->izq << " der : " << p->der << endl;
	cout << "q_0 = " << q << " prior : " << q->prior << " elem : " << q->elem << endl;
	cout << " - - - - padre : " << q->padre << " izq : " << q->izq << " der : " << q->der << endl;*/
	typename ColaMinPrior<T>::Nodo aux_p = (*p);

	
	if(!p->esRaiz()){
		if(p->padre->izq == p)
			p->padre->setIzq(q);
		else
			p->padre->setDer(q);
	}

	p->izq->setPadre(q);
	p->der->setPadre(q);

	q->izq->setPadre(p);
	q->der->setPadre(p);

	if(p->izq == q || p->der == q){
		p->padre = q;

		if(p->izq == q){
			p->izq = q->izq;
			p->der = q->der;
			q->padre = aux_p.padre;
			q->izq = p;
			q->der = aux_p.der;
		}else{
			p->izq = q->izq;
			p->der = q->der;
			q->padre = aux_p.padre;
			q->izq = aux_p.izq;
			q->der = p;
		}
	} else {
		p->izq = q->izq;
		p->der = q->der;
		if(q->padre != NULL){
			if(q->padre->izq == q)
				q->padre->izq = p;
			else
				q->padre->der = p;
		}
		q->padre = aux_p.padre;
		q->izq->padre = aux_p.padre;
		q->der->padre = aux_p.padre;
		
		q->izq = aux_p.izq;
		q->der = aux_p.der;	
	}

	if(_proximo == p){
		_proximo = q;
	}
	/*cout << "p = " << p << " prior : " << p->prior << " elem : " << p->elem << endl;
	cout << " - - - - padre : " << p->padre << " izq : " << p->izq << " der : " << p->der << endl;
	cout << "q = " << q << " prior : " << q->prior << " elem : " << q->elem << endl;
	cout << " - - - - padre : " << q->padre << " izq : " << q->izq << " der : " << q->der << endl;*/
}

template <class T>
void ColaMinPrior<T>::mostrar(std::ostream& os) const{
	os << "heap: ";
	mostrarNodo(os,_proximo);

	if (checkNodos()){
		os << "nodos chequeados ok..." << endl;
	}else{
		os << "Oh no! Algo no esta bien!!!" << endl;
	}
}

template <typename T>
void ColaMinPrior<T>::mostrarNodo(std::ostream& os, typename ColaMinPrior<T>::Nodo* const p) const{
	cout << "p = " << p << " prior : " << p->prior << " elem : " << p->elem << endl;
	cout << " - - - - padre : " << p->padre << " izq : " << p->izq << " der : " << p->der << endl;

	if (p->izq != NULL){
		mostrarNodo(os, p->izq);
	}

	if (p->der != NULL){
		mostrarNodo(os, p->der);
	}
}

template <typename T>
bool ColaMinPrior<T>::checkNodos() const{
	bool res = EsVacia();

	if (!res){
		res = (_proximo->padre == NULL) && checkNodo(_proximo->izq, true) && checkNodo(_proximo->der, false);
	}
}

template <typename T>
bool ColaMinPrior<T>::checkNodo(typename ColaMinPrior<T>::Nodo* const p, bool izq) const{
	bool res = (p == NULL);
	if(!res){
		if (izq) {
			res = (p->padre->izq == p);
			if (!res)
				cout << "falso hijo izquierdo en " << p << " prior: " << p->prior << " elem:" << p->elem << endl; 
		}else{
			res = (p->padre->der == p);
			if (!res)
				cout << "falso hijo derecho" << p << " prior: " << p->prior << " elem:" << p->elem << endl; 
		}
		res = res && checkNodo(p->izq, true) && checkNodo(p->der, false);
	}
	return res;
}

/*
template <typename T>
void Lista<T>::Comienzo()
{
  #ifdef DEBUG
  assert( ! EsVacia() );
  #endif

  CrearItUlt().EliminarAnterior();
}
*/

template <typename T>
typename ColaMinPrior<T>::Iterador ColaMinPrior<T>::CrearIt()
{
  return Iterador(this, _proximo);
}
/*template <typename T>
typename ColaMinPrior<T>::Iterador ColaMinPrior<T>::CrearItUlt()
{
  return Iterador(this, NULL);
}*/
template <typename T>
typename ColaMinPrior<T>::const_Iterador ColaMinPrior<T>::CrearIt() const
{
  return const_Iterador(this, _proximo);
}
/*
template <typename T>
typename ColaMinPrior<T>::const_Iterador ColaMinPrior<T>::CrearItUlt() const
{
  return const_Iterador(this, NULL);
}*/
  // Implementacion Iterador

template <typename T>
ColaMinPrior<T>::Iterador::Iterador()
  : _cola(NULL), _nodo_siguiente(NULL)
{}

template <typename T>
ColaMinPrior<T>::Iterador::Iterador(const typename ColaMinPrior<T>::Iterador& otro)
  : _cola(otro._cola), _nodo_siguiente(otro._nodo_siguiente)
{}

template <typename T>
typename ColaMinPrior<T>::Iterador& ColaMinPrior<T>::Iterador::operator= (const typename ColaMinPrior<T>::Iterador& otro)
{
	_cola = otro._cola;
	_nodo_siguiente = otro._nodo_siguiente;

  return *this;
}

template <typename T>
bool ColaMinPrior<T>::Iterador::HaySiguiente() const
{
  return _nodo_siguiente != NULL;
}

template <typename T>
T& ColaMinPrior<T>::Iterador::Siguiente()
{
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  return _nodo_siguiente->elem;
}

template <typename T>
const T& ColaMinPrior<T>::Iterador::Siguiente() const
{
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  return _nodo_siguiente->elem;
}

template <typename T>
void ColaMinPrior<T>::Iterador::EliminarSiguiente() {
#ifdef DEBUG
	assert(HaySiguiente());
#endif
	if (_cola->_tamano > 1) {
		Nodo* ult = _cola->UltimoNodo();
		swapCola(ult, _nodo_siguiente);
		if (_cola->_tamano % 2 == 0) {
			_nodo_siguiente->padre->izq = NULL;
		} else {
			_nodo_siguiente->padre->der = NULL;
		}
		_cola->_tamano--;
		// Bajar(_cola, ult); TODO codear Bajar
	} else {
		_nodo_siguiente = NULL;
		_cola->_tamano = 0;
	}
	_nodo_siguiente->padre = NULL;
}
template<class T>
bool ColaMinPrior<T>::Iterador::operator == (const typename ColaMinPrior<T>::Iterador& otro) const {
  return _cola == otro._cola && _nodo_siguiente == otro._nodo_siguiente;
}

template<class T>
ColaMinPrior<T>::Iterador::Iterador(ColaMinPrior<T>* cola, typename ColaMinPrior<T>::Nodo* proximo)
  : _cola(cola), _nodo_siguiente(proximo)
{};

  // Implementacion const_Iterador

template <typename T>
ColaMinPrior<T>::const_Iterador::const_Iterador()
  : _cola(NULL), _nodo_siguiente(NULL)
{}

template <typename T>
ColaMinPrior<T>::const_Iterador::const_Iterador(const typename ColaMinPrior<T>::const_Iterador& otro)
  : _cola(otro._cola), _nodo_siguiente(otro._nodo_siguiente)
{}

template <typename T>
ColaMinPrior<T>::const_Iterador::const_Iterador(const typename ColaMinPrior<T>::Iterador& otro)
  : _cola(otro._cola), _nodo_siguiente(otro._nodo_siguiente)
{}

template <typename T>
typename ColaMinPrior<T>::const_Iterador& ColaMinPrior<T>::const_Iterador::operator = (const typename ColaMinPrior<T>::const_Iterador& otro)
{
	_cola = otro._cola;
	_nodo_siguiente = otro._nodo_siguiente;

  return *this;
}

template <typename T>
bool ColaMinPrior<T>::const_Iterador::HaySiguiente() const
{
  return _nodo_siguiente != NULL;
}

template <typename T>
const T& ColaMinPrior<T>::const_Iterador::Siguiente() const
{
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  return _nodo_siguiente->elem;
}

template<class T>
bool ColaMinPrior<T>::const_Iterador::operator == (const typename ColaMinPrior<T>::const_Iterador& otro) const {
  return _cola == otro._cola && _nodo_siguiente == otro._nodo_siguiente;
}

template <typename T>
ColaMinPrior<T>::const_Iterador::const_Iterador(const ColaMinPrior<T>* lista, const typename ColaMinPrior<T>::Nodo* proximo)
  : _cola(lista), _nodo_siguiente(proximo)
{}

  // Otros

template <typename T>
std::ostream& operator<<(std::ostream& os, const ColaMinPrior<T>& lista)
{
  return Mostrar(os, lista, '<', '>');
}

#endif // AED2_LISTA_H_INCLUDED

