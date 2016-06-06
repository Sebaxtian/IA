#ifndef AVARA_H
#define AVARA_H


#include <queue>
#include "nodo.h"
#include "entorno.h"
#include <stack>


// Tipos de distancias
// http://wwwae.ciemat.es/~cardenas/docs/lessons/MedidasdeDistancia.pdf
// https://es.wikipedia.org/wiki/Geometr%C3%ADa_del_taxista
// https://es.wikipedia.org/wiki/Distancia_de_Chebyshov [Esta contempla la distancia en diagonales]



class CompararPrioridadHeurista
{
public:
  CompararPrioridadHeurista()
    {}
  bool operator() (const Nodo& nodoA, const Nodo& nodoB) const
  {
     // cout << "nodoA.getCostoAcumulado() = " << nodoA.getCostoAcumulado() << endl;
      Nodo  nodA = nodoA;
      Nodo  nodB = nodoB;
      return (nodA.getHeuristica() >= nodB.getHeuristica());
  }
};


class Avara
{
    priority_queue<Nodo, vector<Nodo>, CompararPrioridadHeurista> colaPrioridadNodos;
    Entorno miEntorno;
    Nodo nodoRaiz;
    bool ind_evita_devolverse;
    int nodosCreados;
    int nodosExpandidos;
    double costoSolucion;
public:
    Avara();
    Avara(Nodo * nodoRaiz, Entorno entorno, bool ind_evita_devol);
    stack<string> pilaCaminoNodosExp;
    string * busquedaAvara();
    int getNodosCreados();
    int getNodosExpandidos();
    double getCostoSolucion();
    void crearHijos(Nodo nodo);
    void crearNodo(int posIHijo, int posJHijo, Nodo nodoCabeza);
    estados toEstado(int itemEntorno);
    double obtenerHeuristica(Nodo pnodo);
};

#endif // AVARA_H
