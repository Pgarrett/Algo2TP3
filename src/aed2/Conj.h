
#ifndef AED2_CONJ_H_INCLUDED
#define	AED2_CONJ_H_INCLUDED

#include <iostream>
#include "Lista.h"

namespace aed2
{

template<class T>
class Conj
{
  public:

    //forward declarations
    class Iterador;
    class const_Iterador;

    // Generadores

    Conj();
    Conj(const Conj<T>& otro);

    Iterador Agregar(const T& e);
    Iterador AgregarRapido(const T& e);

    void Eliminar(const T& e);

    // Observadores

    bool EsVacio() const;

    bool Pertenece(const T& e) const;

    Nat Cardinal() const;

    Iterador CrearIt();
    const_Iterador CrearIt() const;

    //esta funcion la agregamos aca, porque nos conviene acceder a
    //la representación.  Sino, no haria falta.
    bool operator == (const Conj<T>& otro) const;

    /************************************
    * Iterador de Conjunto, modificable *
    ************************************/
    class Iterador
    {
      public:

        Iterador();

        Iterador(const typename Conj<T>::Iterador& otra);

        Iterador& operator = (const typename Conj<T>::Iterador& otra);

        bool operator == (const typename Conj<T>::Iterador& otro) const;

        bool HaySiguiente() const;
        bool HayAnterior() const;

        T& Siguiente();
        T& Anterior();

        const T& Siguiente() const;
        const T& Anterior() const;

        void Avanzar();
        void Retroceder();

        void EliminarAnterior();
        void EliminarSiguiente();

      private:
      
        typename Lista<T>::Iterador _it_lst;

        Iterador(Conj<T>& c);

        Iterador(const typename Lista<T>::Iterador& itLst);

        friend class Conj<T>::const_Iterador;

        friend typename Conj<T>::Iterador Conj<T>::CrearIt();
        friend typename Conj<T>::Iterador Conj<T>::Agregar(const T&);
        friend typename Conj<T>::Iterador Conj<T>::AgregarRapido(const T&);
    };

    /*********************************************
    * const_Iterador de Conjunto, no modificable *
    *********************************************/
    class const_Iterador
    {
      public:

        const_Iterador();

        const_Iterador(const typename Conj<T>::Iterador& otra);

        const_Iterador(const typename Conj<T>::const_Iterador& otra);

        const_Iterador& operator = (const typename Conj<T>::const_Iterador& otra);

        bool operator==(const typename Conj<T>::const_Iterador& otro) const;

        bool HaySiguiente()const;
        bool HayAnterior()const;

        const T& Siguiente()const;
        const T& Anterior()const;

        void Avanzar();
        void Retroceder();

      private:

        typename Lista<T>::const_Iterador _it_lst;

        const_Iterador(const Conj<T>& c);

        friend typename Conj<T>::const_Iterador Conj<T>::CrearIt() const;

    };

  private:

    Lista<T> _lst;
};

template<class T>
std::ostream& operator<<(std::ostream&, const Conj<T>&);

template<class T>
bool operator==(const Conj<T>&, const Conj<T>&);

  //  Implementacion de Conjunto

template<class T>
Conj<T>::Conj()
{}

template<class T>
Conj<T>::Conj(const Conj<T>& otro)
  : _lst( otro._lst )
{}

template<class T>
typename Conj<T>::Iterador Conj<T>::Agregar(const T& e){
    return Iterador(_lst.AgregarAtras(e));
}

template<class T>
typename Conj<T>::Iterador Conj<T>::AgregarRapido(const T& e){
    return Iterador(_lst.AgregarAtras(e));
}

template<class T>
void Conj<T>::Eliminar(const T& e){
    typename Lista<T>::Iterador it = _lst.CrearIt();
    bool eliminado = false;

    while(it.HaySiguiente() && !eliminado){
      if (it.Siguiente() == e){
        it.EliminarSiguiente();
        eliminado = true;
      }
      it.Avanzar();
    }
}

template<class T>
bool Conj<T>::EsVacio() const{
    return _lst.Longitud()==0;
}

template<class T>
bool Conj<T>::Pertenece(const T& e) const{
    typename Lista<T>::const_Iterador it = _lst.CrearIt();
    bool encontrado = false;

    while(it.HaySiguiente() && !encontrado){
      encontrado = (it.Siguiente() == e);
      it.Avanzar();
    }

    return(encontrado);
}

template<class T>
Nat Conj<T>::Cardinal() const{
    return _lst.Longitud();
}

template<class T>
bool Conj<T>::operator==(const Conj<T>& otro) const {
    return _lst == otro._lst; //Esto no va a funcionar muy bien
}

template<class T>
typename Conj<T>::Iterador Conj<T>::CrearIt(){
    return Iterador(*this);
}

template<class T>
typename Conj<T>::const_Iterador Conj<T>::CrearIt() const{
    return const_Iterador(*this);
}

  // Implementacion Iterador

template<class T>
Conj<T>::Iterador::Iterador(const typename Conj<T>::Iterador& otra)
  : _it_lst(otra._it_lst)
{}

template<class T>
typename Conj<T>::Iterador& Conj<T>::Iterador::operator = (const typename Conj<T>::Iterador& otra){
  _it_lst = otra._it_lst;
  return *this;
}

template<class T>
Conj<T>::Iterador::Iterador()
{}

template<class T>
bool Conj<T>::Iterador::operator == (const typename Conj<T>::Iterador& otro) const{
  return _it_lst == otro._it_lst;
}

template<class T>
bool Conj<T>::Iterador::HaySiguiente() const{
  return _it_lst.HaySiguiente();
}

template<class T>
bool Conj<T>::Iterador::HayAnterior() const{
  return _it_lst.HayAnterior();
}

template<class T>
const T& Conj<T>::Iterador::Siguiente() const{
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  return _it_lst.Siguiente();
}

template<class T>
const T& Conj<T>::Iterador::Anterior() const{
  #ifdef DEBUG
  assert( HayAnterior() );
  #endif

  return _it_lst.Anterior();
}

template<class T>
T& Conj<T>::Iterador::Siguiente(){
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  return _it_lst.Siguiente();
}

template<class T>
T& Conj<T>::Iterador::Anterior(){
  #ifdef DEBUG
  assert( HayAnterior() );
  #endif

  return _it_lst.Anterior();
}

template<class T>
void Conj<T>::Iterador::Avanzar(){
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  _it_lst.Avanzar();
}

template<class T>
void Conj<T>::Iterador::Retroceder(){
  #ifdef DEBUG
  assert( HayAnterior() );
  #endif

  _it_lst.Retroceder();
}

template<class T>
void Conj<T>::Iterador::EliminarAnterior(){
  #ifdef DEBUG
  assert( HayAnterior() );
  #endif

  _it_lst.EliminarAnterior();
}

template<class T>
void Conj<T>::Iterador::EliminarSiguiente(){
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  _it_lst.EliminarSiguiente();
}

template<class T>
Conj<T>::Iterador::Iterador(Conj<T>& c)
  : _it_lst(c._lst.CrearIt())
{}

template<class T>
Conj<T>::Iterador::Iterador(const typename Lista<T>::Iterador& iter)
  : _it_lst(iter)
{}

  // Implementacion const_Iterador

template<class T>
Conj<T>::const_Iterador::const_Iterador()
{}

template<class T>
Conj<T>::const_Iterador::const_Iterador(const typename Conj<T>::Iterador& otra)
  : _it_lst( otra._it_lst )
{}

template<class T>
Conj<T>::const_Iterador::const_Iterador(const typename Conj<T>::const_Iterador& otra)
  : _it_lst( otra._it_lst )
{}

template<class T>
typename Conj<T>::const_Iterador& Conj<T>::const_Iterador::operator = (const typename Conj<T>::const_Iterador& otra){
  _it_lst = otra._it_lst;

  return *this;
}

template<class T>
bool Conj<T>::const_Iterador::operator == (const typename Conj<T>::const_Iterador& otro) const{
  return _it_lst == otro._it_lst;
}

template<class T>
bool Conj<T>::const_Iterador::HaySiguiente() const{
  return _it_lst.HaySiguiente();
}

template<class T>
bool Conj<T>::const_Iterador::HayAnterior() const{
  return _it_lst.HayAnterior();
}

template<class T>
const T& Conj<T>::const_Iterador::Siguiente() const{
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  return _it_lst.Siguiente();
}

template<class T>
const T& Conj<T>::const_Iterador::Anterior() const{
  #ifdef DEBUG
  assert( HayAnterior() );
  #endif

  return _it_lst.Anterior();
}

template<class T>
void Conj<T>::const_Iterador::Avanzar(){
  #ifdef DEBUG
  assert( HaySiguiente() );
  #endif

  _it_lst.Avanzar();
}

template<class T>
void Conj<T>::const_Iterador::Retroceder(){
  #ifdef DEBUG
  assert( HayAnterior() );
  #endif

  _it_lst.Retroceder();
}

template<class T>
Conj<T>::const_Iterador::const_Iterador(const Conj<T>& c)
  : _it_lst(c._lst.CrearIt())
{}

  // Otras implementaciones

template<class T>
bool operator==(const Conj<T>& c1, const Conj<T>& c2){
  return c1.operator==(c2);
}

template<class T>
std::ostream& operator<<(std::ostream& os, const Conj<T>& c){
  return Mostrar(os, c, '{', '}');
}

}

#endif	//AED2_CONJ_H_INCLUDED
