#include "amplitud.h"
#include "nodo.h"
#include <iostream>
#include <queue>
#include <string>
#include <string.h>

using namespace std;


Amplitud::Amplitud()
{

}

Amplitud::Amplitud(Nodo *nodoRaiz, Entorno entorno)
{

    this->colaNodos.push(*nodoRaiz);
    this->miEntorno = entorno;
    this->nodoRaiz = *nodoRaiz;
    this->nodosCreados = 0;
    this->nodosExpandidos = 0;
}

Nodo *Amplitud::busquedaPreferente() {
    cout << "Inicia Busqueda Preferente" << endl;


    bool termina = false;
    Nodo *solucion;
    int parada = 30000000;
    Nodo nodoCabeza;
    while(!termina && parada > 0) {
        // Si la cola esta vacia
        if(colaNodos.empty()) {
            termina = true;
        } else {
            nodoCabeza = colaNodos.front();
            colaNodos.pop();
            pilaNodosExp.push(nodoCabeza);
            // Aumenta los nodos expandidos
            nodosExpandidos++;
            // Si el nodo cabeza es meta
            if(nodoCabeza.esMeta()) {
                // Terminar, encontro solucion
                solucion = &pilaNodosExp.top();
                //return solucion;


                termina = true;
            } else {
                // Expandir y meter nodos al final de la cola
                expandirNodos(nodoCabeza);
            }
            /*
            if (nodoCabeza.get_indMeta() >=2) {

                cout << " NC : " << nodosCreados<< " => inMeta : " << nodoCabeza.get_indMeta() <<  " => inMeta : " << nodoCabeza.get_indMeta() <<  " => Prof : " << nodoCabeza.getProfundidad() <<  " ***** "  << endl;
            }
            */
        }
        parada--;
    }
    cout << "HOLA !!" << endl;

    cout << " NC : " << nodosCreados << " => inMeta : " << nodoCabeza.get_indMeta() <<  " => Prof : " << nodoCabeza.getProfundidad() <<  " ***** "  << endl;

    return solucion;
}


void Amplitud::expandirNodos(Nodo nodo) {
    // Estos son los limites para expandir
    int limFilas = miEntorno.getAlto();
    int limColums = miEntorno.getAncho();
    int roca = 1;
    int humano = 8;

    // Si el nodo es el humano
    if(nodo.getCodNodo() != humano) {
        int posI = nodo.get_fila();
        int posJ = nodo.get_columna();
        int derecha = posJ + 1;
        int abajo = posI + 1;
        int izquierda = posJ - 1;
        int arriba = posI - 1;
        // Si se puede mover a la derecha
        if(derecha < limColums && miEntorno.getAmbiente()[posI][derecha] != roca) {
            Nodo nodoHijo(posI, derecha, miEntorno.getAmbiente()[posI][derecha]);
            /*queue<string> pasosSolPapa = nodo.get_pasosSolucion();
            nodoHijo.set_pasosSolucion(&pasosSolPapa);
            nodoHijo.set_pasosSolucion(to_string(posI) + "," + to_string(derecha));*/
            nodoHijo.setProfundidad(nodo.getProfundidad() + 1);
            nodoHijo.set_indMeta(nodo.get_indMeta());
            nodoHijo.set_padre(&pilaNodosExp.top());
            // nodos creados aumenta
            nodosCreados++;
            // Agrega el nodo a la cola
            colaNodos.push(nodoHijo);
        }
        // Si se puede mover abajo
        if(abajo < limFilas && miEntorno.getAmbiente()[abajo][posJ] != roca) {
            Nodo nodoHijo(abajo, posJ, miEntorno.getAmbiente()[abajo][posJ]);
            /*queue<string> pasosSolPapa = nodo.get_pasosSolucion();
            nodoHijo.set_pasosSolucion(&pasosSolPapa);
            nodoHijo.set_pasosSolucion(to_string(abajo) + "," + to_string(posJ));*/
            nodoHijo.setProfundidad(nodo.getProfundidad() + 1);
            nodoHijo.set_indMeta(nodo.get_indMeta());
            nodoHijo.set_padre(&pilaNodosExp.top());
            // nodos creados aumenta
            nodosCreados++;
            // Agrega el nodo a la cola
            colaNodos.push(nodoHijo);
        }
        // Si se puede mover a izquierda
        if(izquierda >= 0 && miEntorno.getAmbiente()[posI][izquierda] != roca) {
            Nodo nodoHijo(posI, izquierda, miEntorno.getAmbiente()[posI][izquierda]);
            /*queue<string> pasosSolPapa = nodo.get_pasosSolucion();
            nodoHijo.set_pasosSolucion(&pasosSolPapa);
            nodoHijo.set_pasosSolucion(to_string(posI) + "," + to_string(izquierda));*/
            nodoHijo.setProfundidad(nodo.getProfundidad() + 1);
            nodoHijo.set_indMeta(nodo.get_indMeta());
            nodoHijo.set_padre(&pilaNodosExp.top());
            // nodos creados aumenta
            nodosCreados++;
            // Agrega el nodo a la cola
            colaNodos.push(nodoHijo);
        }
        // Si se puede mover arriba
        if(arriba >= 0 && miEntorno.getAmbiente()[arriba][posJ] != roca) {
            Nodo nodoHijo(arriba, posJ, miEntorno.getAmbiente()[arriba][posJ]);
            /*queue<string> pasosSolPapa = nodo.get_pasosSolucion();
            nodoHijo.set_pasosSolucion(&pasosSolPapa);
            nodoHijo.set_pasosSolucion(to_string(arriba) + "," + to_string(posJ));*/
            nodoHijo.setProfundidad(nodo.getProfundidad() + 1);
            nodoHijo.set_indMeta(nodo.get_indMeta());
            nodoHijo.set_padre(&pilaNodosExp.top());
            // nodos creados aumenta
            nodosCreados++;
            // Agrega el nodo a la cola
            colaNodos.push(nodoHijo);
        }
        /*
        queue<Nodo> colaNodos2 = colaNodos;
        while (!colaNodos2.empty()) {
            cout << "codNodo: " << colaNodos2.front().getCodNodo() << " = " << colaNodos2.front().get_fila() << " , " << colaNodos2.front().get_columna() << endl;
            colaNodos2.pop();
        }
        cout << " --- ---- --- " << endl;
        */
    }
}
