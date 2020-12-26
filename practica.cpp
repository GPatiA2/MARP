/*
 * practica.cpp
 *
 *  Created on: 25 dic. 2020
 *      Author: Guille
 */

#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include <vector>
#include <limits.h>
#include <unordered_map>
#include "skew_heap.h"
using namespace std;





struct arista{
	int o;
	int d;
	int c;

	arista(int origen, int destino, int coste): o(origen), d(destino), c(coste) {}

	bool operator == (arista const& other){
		return this->o == other.o && this->d == other.d && this->c == other.c;
	}
};

struct comp{

	bool operator() (arista const& a1, arista const& a2){
		if(a1.c < a2.c){
			return true;
		}
		else{
			return false;
		}
	}

};

using skew_heap = generic_skew_heap<const arista, comp>;

skew_heap obtenerDatos(unordered_set<int> & v){

	for(int i = 1; i < 12; i++){
		v.insert(i);
	}

	skew_heap ar;

	ar.insert(arista(1,3,10));
	ar.insert({2,8,40});
	ar.insert({3,4,38});
	ar.insert({3,5,41});
	ar.insert({4,10, 24});
	ar.insert({5,6, 25});
	ar.insert({5,7, 83});
	ar.insert({6,8, 60});
	ar.insert({7,10, 13});
	ar.insert({7,9, 17});
	ar.insert({8,9, 60});
	ar.insert({9,11, 31});
	ar.insert({10,11, 14});

	ar.insert({2,1, 30});
	ar.insert({3,1, 10});
	ar.insert({8,2, 40});
	ar.insert({4,3, 38});
	ar.insert({5,3, 41});
	ar.insert({10,4, 24});
	ar.insert({6,5, 25});
	ar.insert({7,5, 83});
	ar.insert({8,6, 60});
	ar.insert({10,7, 13});
	ar.insert({9,7, 17});
	ar.insert({9,8, 60});
	ar.insert({11,9, 31});
	ar.insert({11,10, 14});

	return ar;
}


void dijkstra(int v0, unordered_set<int> & v, skew_heap & a){

	vector<int> distancias;
	vector<int> predecesores;
	for(int i = 0; i < v.size(); i++){
		distancias[i] = INT_MAX;
		predecesores[i] = v0;
	}

	for(int j = 0; j < v.size()-2; j++){


	}
}

int main(){

	unordered_set<int> v;
	//skew_heap a;
	//a = obtenerDatos(v);
	//dijkstra(v,a);

	generic_skew_heap<int> m;

	for(int j = 10; j > 0; j--){
		m.insert(j);
		if(j == 7 || j == 3 || j == 1){
			m.borra_Min();
		}
	}

	int c = m.getElems();
	m.sacaElementos();
	for(int i = 1; i < c; i++){
		int e = m.borra_Min();
		cout << e << " ";
	}


	return 0;
}

