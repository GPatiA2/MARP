/*
 * Guillermo Garcia Patiño Lenza
 * MAR Grupo A
 * practica.cpp
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


void dijsktra(grafo<int> const & g, grafo<int>::vertice const & v0, bool m){
	using node = grafo<int>::vertice;


	skew_heap h;
	unordered_map<node,int> distancias;
	unordered_map<node,node> predecesores;
	int nv = g.getNumVertices();

	// inicializacion de vectores de distancias y predecesores, y
	//	del monticulo binario
	for(auto &v : g.vertSet()){
		if(v != v0){
			h.insert(v, INT_MAX);
			distancias[v] = INT_MAX;
			predecesores[v] = v0;
		}
	}

	/*
	 * Reduzco las distancias de los vertices adyacentes
	 *  al inicial en el mapa y en el monticulo
	 */
	for(grafo<int>::gnode ng : g.adyacentes(v0)){
		h.decrease_key(ng->vert, ng->cost);
		distancias[ng->vert] = ng->cost;
		predecesores[ng->vert] = v0;
	}

	/*
	 * Bucle principal del algoritmo. Sigue el esquema voraz visto
	 *   en clase de teoria
	 */
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

	/*
	 * Muestra el resultado (solo en showmode)
	 */
	if(m){
		for(auto p : distancias){
			cout << " Nodo " << p.first << " distancia " << p.second << " predecesor " << predecesores[p.first] << endl;
		}
	}

}

void showmode(int initial_nodes, int max_weight, float edge_chance){
	graph_generator gg (initial_nodes, edge_chance, max_weight);
	grafo<int> g = gg.generar(false);
	cout << "Se ha generado el siguiente grafo: " << endl;
	cout << g.print() << endl;
	dijsktra(g, g.getFirst(), true);
}

void timemode(int initial_nodes, int max_nodes, int inc, int max_weight, float edge_chance){
	graph_generator gg(1,edge_chance,max_weight);
	cout << "# Vertices" << "	" << "Tiempo" << endl;
	for(int i = initial_nodes; i < max_nodes ; i+= inc){
		gg.setNumVertices(i);
		float tiempo = 0;
		for(int j = 0; j < 3; j++){
			grafo<int> g = gg.generar(true);
			auto start = std::chrono::steady_clock::now();
			dijsktra(g, g.getFirst(), false);
			auto end = std::chrono::steady_clock::now();
			tiempo += std::chrono::duration<double, std::milli>(end - start).count();
		}

		tiempo = tiempo / 3.0;
		if(tiempo < 10.0){
			tiempo = 0;
			for(int j = 0; j < 100; j++){
				grafo<int> g = gg.generar(true);
				auto start = std::chrono::steady_clock::now();
				dijsktra(g, g.getFirst(), false);
				auto end = std::chrono::steady_clock::now();
				tiempo += std::chrono::duration<double, std::milli>(end - start).count();
			}

			tiempo = tiempo / 100.0;
		}
		cout << i << "	" << tiempo << '\n';

	}

	cout << "DONE" << endl;
}

int main(int argc, char * argv[]){
	if(argc < 6 || argc > 7){
		cout << "Error: Usage is ./practica <-s/-t> <initial_nodes> <max nodes> <inc> <max_weight> <edge_chance>" << endl;
		return 0;
	}

	string maux = argv[1];
	bool mode = (maux == "-s")? true : (maux == "-t")? false : throw invalid_argument("El primer argumento debe ser o -s (showmode) o -t (timemode) \n");
	int initial_nodes = std::stoi(argv[2]);
	int max_nodes = std::stoi(argv[3]);
	int inc = std::stoi(argv[4]);
	int max_weight = std::stoi(argv[5]);
	float edge_chance = std::stof(argv[6]);

	if(mode){
		showmode(initial_nodes, max_weight, edge_chance);
	}
	else{
		timemode(initial_nodes, max_nodes, inc, max_weight, edge_chance);
	}


	return 0;
}

