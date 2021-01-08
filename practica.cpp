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


	skew_heap h;
	unordered_map<node,int> distancias;
	unordered_map<node,node> predecesores;
	int nv = g.getNumVertices();

	//inicializacion de vectores de distancias y predecesores
	for(auto &v : g.vertSet()){
		if(v != v0){
			h.insert(v, INT_MAX);
			distancias[v] = INT_MAX;
			predecesores[v] = v0;
		}
	}

	//inicializacion de monticulo
	for(grafo<int>::gnode ng : g.adyacentes(v0)){
		h.decrease_key(ng->vert, ng->cost);
		distancias[ng->vert] = ng->cost;
		predecesores[ng->vert] = v0;
	}

	//Bucle principal
	for(int j = 0; (j < nv-2 ); j++){
		pair<grafo<int>::vertice, int> p = h.borra_Min();
		node actual = p.first;
		for(grafo<int>::gnode ng : g.adyacentes(actual)){
			if(h.contains(ng->vert)){
				if( ng->cost + distancias[actual] < distancias[ng->vert] ){
					distancias[ng->vert] = ng->cost + distancias[actual];
					predecesores[ng->vert] = actual;
					h.decrease_key(ng->vert, distancias[ng->vert]);
				}
			}
			else{
//				cout << "FALSE" << endl;
			}
		}

	}
	cout << "DONE ";
}

int main(){

	graph_generator gg(15000,0.7,70);
	for(int i = 0; i < 3 ; i++){
		grafo<int> g = gg.generar(true);
		dijsktra(g, g.getFirst());
		cout << i << endl;
	}
	cout << "DONE" << endl;

	return 0;
}

