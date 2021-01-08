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

//	cout << "El vertice inicial es " << v0 << endl;

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
//		string s  = (h.empty())? "VACIO" : "NO VACIO";
//		cout <<"J = "<<  j << " " << s << endl;
		pair<grafo<int>::vertice, int> p = h.borra_Min();
//		cout << " VERTICE ACTUAL = " << p.first << endl;
		node actual = p.first;
		for(grafo<int>::gnode ng : g.adyacentes(actual)){
//			cout << " MIRANDO " << ng->vert << endl;
			if(h.contains(ng->vert)){
//				cout << "TRUE" << endl;
				if( ng->cost + distancias[actual] < distancias[ng->vert] ){
//					cout << "ACTUALIZANDO" << endl;
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
//	for(auto p : distancias){
//		if (p.second == INT_MAX){
//			cout << "Vertice " << p.first << " distancia = UNREACHABLE "  << " predecesor = " << predecesores.at(p.first) << endl;
//		}
//		else{
//			cout << "Vertice " << p.first << " distancia = " << p.second  << " predecesor = " << predecesores.at(p.first) << endl;
//		}
//	}
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

	graph_generator gg(5000,0.7,70);
	for(int i = 0; i < 3 ; i++){
		grafo<int> g = gg.generar(true);
//		cout << g.print() << endl;
//		cout << g.adyMat() << endl;
		dijsktra(g, g.getFirst());
		cout << i << endl;
	}
	cout << "DONE" << endl;

//	skew_heap h;
//	for(int i = 1; i < 10; i+= 2){
//		cout << "Inserto " << i << endl;
//		h.insert(i,i);
//	}
//
//	for(int i = 0; i < 10; i+= 2){
//		cout << "Inserto " << i << endl;
//		h.insert(i,i);
//	}
//
//	while(!h.empty()){
//		pair<int,int> p =h.borra_Min();
//		cout << "He borrado " << p.first << endl;
//	}


	return 0;
}

