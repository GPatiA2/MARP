/*
 * practica.cpp
 *
 *  Created on: 25 dic. 2020
 *      Author: Guille
 */

#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>
#include <limits.h>
#include <unordered_map>
#include "skew_heap.h"
#include "grafo.h"
#include "graph_generator.h"
using namespace std;


void dijsktra(grafo<int> const & g, grafo<int>::vertice const & v0){
	using node = grafo<int>::vertice;

	cout << "El vertice inicial es " << v0 << endl;

	skew_heap h;
	vector<int> distancias;
	vector<int> predecesores;
	unordered_map<node, bool> candidatos;
	int nv = g.getNumVertices();

	//inicializacion de vectores de distancias y predecesores
	for(auto &v : g.vertSet()){
		candidatos[v] = true;
		h.insert(v, INT_MAX);
		distancias.push_back(INT_MAX);
		predecesores.push_back(v0);
	}

	//inicializacion de monticulo
	for(grafo<int>::gnode ng : g.adyacentes(v0)){
		h.insert(ng->vert, ng->cost);
		distancias[ng->vert - 1] = ng->cost;
		predecesores[ng->vert - 1] = v0;
	}

	//Saco el vertice inicial de los candidatos
	candidatos[v0] = false;

	//Bucle principal

	for(int j = 0; j < nv-2; j++){
		cout <<"J = "<<  j << endl;
		pair<grafo<int>::vertice, int> p = h.borra_Min();
		node actual = p.first;
		candidatos[p.first] = false;
		for(grafo<int>::gnode ng : g.adyacentes(actual)){
			if(candidatos[ng->vert]){
				if( ng->cost + distancias[actual - 1] < distancias[ng->vert - 1] ){
					distancias[ng->vert - 1] = ng->cost + distancias[actual - 1];
					predecesores[ng->vert - 1] = actual;
					h.decrease_key(ng->vert, distancias[ng->vert - 1]);
				}
			}
		}

	}

	for(unsigned int i = 0; i < distancias.size(); i++){
		cout << "Vertice " << i+1 << " distancia = " << distancias[i] << " predecesor = " << predecesores[i] << endl;
	}
}

void rellenarGrafo(grafo<int> & g){

	for(int i = 1; i < 12; i++){
		g.insertarVertice(i);
	}

	g.crearArista(1,2,30);
	g.crearArista(1,3,10);
	g.crearArista(2,8,40);
	g.crearArista(3,4,38);
	g.crearArista(3,5,41);
	g.crearArista(4,10,24);
	g.crearArista(5,6,25);
	g.crearArista(5,7,83);
	g.crearArista(6,8,60);
	g.crearArista(7,10,13);
	g.crearArista(7,9,17);
	g.crearArista(8,9,22);
	g.crearArista(9,11,31);
	g.crearArista(10,11,14);

	g.crearArista(1,2,30);
	g.crearArista(3,1,10);
	g.crearArista(8,2,40);
	g.crearArista(4,3,38);
	g.crearArista(5,3,41);
	g.crearArista(10,4,24);
	g.crearArista(6,5,25);
	g.crearArista(7,5,83);
	g.crearArista(8,6,60);
	g.crearArista(10,7,13);
	g.crearArista(9,7,17);
	g.crearArista(9,8,22);
	g.crearArista(11,9,31);
	g.crearArista(11,10,14);

}


int main(){

//	grafo<int> g;
//	rellenarGrafo(g);

	graph_generator gg(5,0.5,50);
	grafo<int> g = gg.generar(false);
	cout << g.print() << endl;
	dijsktra(g, g.getFirst());


	return 0;
}

