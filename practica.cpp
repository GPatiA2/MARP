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
#include <ctime>
#include <chrono>
#include <cmath>
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
		}

	}
}

int main(int argc, char * argv[]){
	if(argc < 4 || argc > 5){
		cout << "Error: Usage is ./practica <initial_nodes> <max nodes> <inc> <max_weight>" << endl;
		return 0;
	}

	graph_generator gg(1,0.5,std::stoi(argv[4]));
	cout << "# Vertices" << "	" << "Tiempo" << endl;
	for(int i = std::stoi(argv[1]); i < std::stoi(argv[2]) ; i+=std::stoi(argv[3])){
		gg.setNumVertices(i);
		float tiempo = 0;
		for(int j = 0; j < 3; j++){
			grafo<int> g = gg.generar(true);
			auto start = std::chrono::steady_clock::now();
			dijsktra(g, g.getFirst());
			auto end = std::chrono::steady_clock::now();
			tiempo += std::chrono::duration<double, std::milli>(end - start).count();
		}

		tiempo = tiempo / 3.0;

		cout << i << "	" << tiempo << '\n';

	}

	cout << "DONE" << endl;

	return 0;
}

