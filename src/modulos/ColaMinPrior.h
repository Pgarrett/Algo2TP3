#ifndef AED2_COLAMINPRIOR_H_
#define AED2_COLAMINPRIOR_H_

#include <ostream>
#include "../aed2/TiposBasicos.h"
#include "../aed2/Lista.h"
#include "../aed2/Arreglo.h"

using namespace aed2;
using namespace std;

template <typename T>
class ColaMinPrior{
  	public:
	class Iterador;
  	/// Crea una Cola Vacía. (Operación Vacia())
  	ColaMinPrior();

  	/// Crea por copia una cola (operación Copiar())
	// ColaMinPrior(const ColaMinPrior& otra);

	/// Destruye la Cola, incluyendo los T alojados
  	~ColaMinPrior();

  	/// Opreaciones básicas
  	bool EsVacia() const;
  	Nat Tamano() const;

  	/// Acceso al proximo (en O(1))
  	T& Proximo();
    const T& Proximo() const;

  	void Desencolar();
  	Iterador Encolar(Nat prior, const T& elem);

  	//void EliminarSiguiente();

	Iterador CrearIt();
	/*
	void mostrar(ostream&) const;
	friend ostream& operator<<(ostream& os, const ColaMinPrior<T> &c) {
		c.mostrar(os);
		return os;
	}*/

  /***********************
   * Iterador de Cola *
   ***********************/
  class Iterador{
	public:
      	Iterador();
		bool HaySiguiente() const;
		T& Siguiente();
		const T& Siguiente() const;
		void EliminarSiguiente();
		//bool operator == (const typename ColaMinPrior<T>::Iterador& otro) const;
        Iterador& operator= (const Iterador& otro);
  	private:
      	ColaMinPrior<T>* _cola;
      	typename ColaMinPrior<T>::Nodo* _nodo_siguiente;

		Iterador(ColaMinPrior<T>* cola, typename ColaMinPrior<T>::Nodo* proximo);
		friend typename ColaMinPrior<T>::Iterador ColaMinPrior<T>::CrearIt();
    	friend typename ColaMinPrior<T>::Iterador ColaMinPrior<T>::CrearItEncolado(typename ColaMinPrior<T>::Nodo*);
	};

private:

	struct Nodo{
		Nodo(const Nat p, const T& d) : prior(p), elem(d), padre(NULL), izq(NULL), der(NULL){};
		
		Nat prior;
		T elem;
		Nodo* padre;
		Nodo* izq;
		Nodo* der;

	    //Algunas funciones muuuuy practicas.
	    void setPadre(Nodo* p){if (this != NULL){padre = p;}}	
		void setIzq(Nodo* p){if (this != NULL){izq = p;}}
		void setDer(Nodo* p){if (this != NULL){der = p;}}
		bool esRaiz(){return (padre == NULL);}
 	};

 	//Metodos privados:
	typename ColaMinPrior<T>::Nodo* UltimoNodo();
	Arreglo<int>* DecimalABinario(Nat);
	void swapCola(typename ColaMinPrior<T>::Nodo* p, typename ColaMinPrior<T>::Nodo* q);
	Nodo* padreNuevoNodo();
	void subir(typename ColaMinPrior<T>::Nodo* n);
	void bajar(typename ColaMinPrior<T>::Nodo* n);
//	void mostrarNodo(std::ostream& os, Nodo* const p) const;
//	bool checkNodos() const;
//	bool checkNodo(typename ColaMinPrior<T>::Nodo* const p, bool izq) const;
//	Iterador CrearIt();
	Iterador CrearItEncolado(typename ColaMinPrior<T>::Nodo*);
 	typename ColaMinPrior<T>::Nodo* _proximo;
	Nat _tamano;
};

template <typename T>
ColaMinPrior<T>::ColaMinPrior()
  : _proximo(NULL), _tamano(0)
{}

template <typename T>
ColaMinPrior<T>::~ColaMinPrior(){
  	while(!EsVacia()) {
    	Desencolar();
	}
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

template <typename T>
void ColaMinPrior<T>::Desencolar(){
  	#ifdef DEBUG
  	assert(!EsVacia());
  	#endif
	
	Nodo* n = UltimoNodo();
	swapCola(_proximo,n);
	n = UltimoNodo();
	
	if (_tamano > 1){
		if (_tamano % 2 == 0){
			n->padre->setIzq(NULL);
		}else{
			n->padre->setDer(NULL);
		}
		delete(n);
		bajar(_proximo);
		--_tamano;
	}else{
		delete(_proximo);
		_proximo = NULL;
		_tamano = 0;
	}
 }

template <typename T>
typename ColaMinPrior<T>::Iterador ColaMinPrior<T>::Encolar(const Nat prior, const T& elem){
	Nodo* nuevo = new Nodo(prior,elem);
	if(_proximo == NULL){
		_proximo = nuevo;
		_proximo->padre = NULL;
	}else{
		Nodo* padre = padreNuevoNodo();
		if(padre->izq == NULL){
			padre->izq = nuevo;
		}else{
			padre->der = nuevo;
		}
		nuevo->padre = padre;
	}
	++_tamano;
	typename ColaMinPrior<T>::Iterador res = CrearItEncolado(nuevo);
 	subir(nuevo);
 	return(res);
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
void ColaMinPrior<T>::bajar(typename ColaMinPrior<T>::Nodo* n){
	bool swap = true;
	bool esHoja = (n->izq == NULL && n->der == NULL);
	while(!esHoja && swap){
		swap = false;
		if(n->der == NULL){
			if (n->izq->prior < n->prior){
				swapCola(n, n->izq);
				swap = true;
			}
		}else{
			if(n->izq == NULL){
				if(n->der->prior < n->prior){
					swapCola(n, n->der);
					swap = true;
				}
			}else{
				if(n->der->prior < n->izq->prior){
					if(n->der->prior < n->prior){
						swapCola(n, n->der);
						swap = true;
					}else{
						if (n->izq->prior < n->prior){
							swapCola(n, n->izq);
							swap = true;
						}	
					}
				}else{
					if (n->izq->prior < n->prior){
						swapCola(n, n->izq);
						swap = true;
					}else{
						if(n->der->prior < n->prior){
							swapCola(n, n->der);
							swap = true;
						}
					}	
				}
			}
		}
		esHoja = (n->izq == NULL && n->der == NULL);
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
    delete(a);
    return(n);
}

template <typename T>
typename ColaMinPrior<T>::Nodo* ColaMinPrior<T>::UltimoNodo(){
    Arreglo<int>* a = DecimalABinario(_tamano);
    Nodo* n = _proximo;
    for (int i = 1; i < a->Tamanho(); i++){
        if ((*a)[i] == 0)
        	n = (n->izq);
        else
        	n = (n->der);
    }
    delete(a);
    return(n);
}

template <typename T>
Arreglo<int>* ColaMinPrior<T>::DecimalABinario(Nat d){
	Lista<unsigned int> temp;
	while(d > 0){
		temp.AgregarAdelante(d%2);
		d = (Nat)d/2;
	}
	Nat l = temp.Longitud();
 	Arreglo<int>* res = new Arreglo<int>(l);
	int i = 0;
	typename Lista<unsigned int>::Iterador it = temp.CrearIt();
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

	if(p != q){	
		if(!p->esRaiz()){
			if(p->padre->izq == p)
				p->padre->setIzq(q);
			else
				p->padre->setDer(q);
		}else{
			_proximo = q;
		}

		p->izq->setPadre(q);
		p->der->setPadre(q);

		q->izq->setPadre(p);
		q->der->setPadre(p);

		if(p->izq == q || p->der == q){
			p->setPadre(q);

			if(p->izq == q){
				p->setIzq(q->izq);
				p->setDer(q->der);
				q->setPadre(aux_p.padre);
				q->setIzq(p);
				q->setDer(aux_p.der);
			}else{
				p->setIzq(q->izq);
				p->setDer(q->der);
				q->setPadre(aux_p.padre);
				q->setIzq(aux_p.izq);
				q->setDer(p);
			}
		} else {
//			cout << " caso else " << endl;
			p->setPadre(q->padre);
			p->setIzq(q->izq);
			p->setDer(q->der);
			
			if(q->padre != NULL){
				if(q->padre->izq == q)
					q->padre->setIzq(p);
				else
					q->padre->setDer(p);
			}
			q->setPadre(aux_p.padre);

			q->setIzq(aux_p.izq);
			q->setDer(aux_p.der);	
		}
	}
/*	cout << "p = " << p << " prior : " << p->prior << " elem : " << p->elem << endl;
	cout << " - - - - padre : " << p->padre << " izq : " << p->izq << " der : " << p->der << endl;
	cout << "q = " << q << " prior : " << q->prior << " elem : " << q->elem << endl;
	cout << " - - - - padre : " << q->padre << " izq : " << q->izq << " der : " << q->der << endl;*/
}
/* //   TODO: Borrar antes de entregar (o no, tampoco creo que se vea demasiado mal tener un choclo de funciones comentadas 
		que verifican la estructura)

template <class T>
void ColaMinPrior<T>::mostrar(std::ostream& os) const{
	os << "heap: ";
	
	if (!EsVacia()){
		os << "Raiz -> "; 
		mostrarNodo(os,_proximo);

		bool checkArbol = checkNodos();
		if (checkArbol){
			os << "nodos chequeados ok..." << endl;
		}else{
			os << "Oh no! Algo no esta bien!!!" << endl;
		}
		assert(checkArbol);
	}else{
		os << "vacio!" << endl;
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
	return res;
}

template <typename T>
bool ColaMinPrior<T>::checkNodo(typename ColaMinPrior<T>::Nodo* const p, bool izq) const{
	bool res = (p == NULL);
	if(!res){
		bool bienEncadenado;
		bool invarianteHeap;
		if (izq) {
			bienEncadenado = (p->padre->izq == p);
			if (!bienEncadenado)
				cout << "falso hijo izquierdo en " << p << " prior: " << p->prior << " elem:" << p->elem << endl; 
		}else{
			bienEncadenado = (p->padre->der == p);
			if (!bienEncadenado)
				cout << "falso hijo derecho" << p << " prior: " << p->prior << " elem:" << p->elem << endl; 
		}

		invarianteHeap = (_proximo->prior <= p->prior) && (p->padre->prior <= p->prior);
		if(!invarianteHeap)
			cout << "este nodo hijo con menor prioridad " << p << " prior: " << p->prior << " elem:" << p->elem << endl; 

		res = bienEncadenado && invarianteHeap && checkNodo(p->izq, true) && checkNodo(p->der, false);
	}
	return res;
}
*/
template <typename T>
typename ColaMinPrior<T>::Iterador ColaMinPrior<T>::CrearIt(){
	return Iterador(this, _proximo);
}

template <typename T>
typename ColaMinPrior<T>::Iterador ColaMinPrior<T>::CrearItEncolado(typename ColaMinPrior<T>::Nodo* n){
	return Iterador(this, n);
}

template <typename T>
ColaMinPrior<T>::Iterador::Iterador()
  : _cola(NULL), _nodo_siguiente(NULL)
{}

template<class T>
ColaMinPrior<T>::Iterador::Iterador(ColaMinPrior<T>* cola, typename ColaMinPrior<T>::Nodo* proximo)
  : _cola(cola), _nodo_siguiente(proximo)
{};

template <typename T>
bool ColaMinPrior<T>::Iterador::HaySiguiente() const{
  return _nodo_siguiente != NULL;
}

template <typename T>
T& ColaMinPrior<T>::Iterador::Siguiente(){
  #ifdef DEBUG
  assert(HaySiguiente());
  #endif

  return _nodo_siguiente->elem;
}

template <typename T>
const T& ColaMinPrior<T>::Iterador::Siguiente() const{
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  return _nodo_siguiente->elem;
}

template <typename T> //REVISAR !!! !!! !!! !!! !!! !!! Puede que esto no sea tan feliz.
void ColaMinPrior<T>::Iterador::EliminarSiguiente() {
	#ifdef DEBUG
	assert(HaySiguiente());
	#endif
	if (_cola->_tamano > 1) { 
		Nodo* ult = _cola->UltimoNodo();
		bool borrarUlt = (_nodo_siguiente == ult);

		_cola->swapCola(_nodo_siguiente, ult);
		if (_cola->_tamano % 2 == 0) {
			_nodo_siguiente->padre->setIzq(NULL);
		} else {
			_nodo_siguiente->padre->setDer(NULL);;
		}
		_cola->_tamano--;
		delete(_nodo_siguiente);
		if (!borrarUlt) //No falla pero Valgrind tira error. 
			_cola->bajar(ult);
	} else {
		delete(_cola->_proximo);
		_cola->_proximo = NULL;
		_cola->_tamano = 0;
	}
	_nodo_siguiente = NULL;
}

template <typename T>
typename ColaMinPrior<T>::Iterador& ColaMinPrior<T>::Iterador::operator= (const typename ColaMinPrior<T>::Iterador& otro){
	_cola = otro._cola;
	_nodo_siguiente = otro._nodo_siguiente;
}

#endif //  AED2_COLAMINPRIOR_H_