/*
 * graph_generator.h
 *
 *  Created on: 1 ene. 2021
 *      Author: Guille
 */

#ifndef GRAPH_GENERATOR_H_
#define GRAPH_GENERATOR_H_

#include <stdlib.h>
#include "grafo.h"
#include <time.h>
using namespace std;

class graph_generator{

	int numVertices;
	float prob_arista;
	int coste_maximo;

public:

	graph_generator(int nv, float a, int cM) : numVertices(nv), prob_arista(a), coste_maximo(cM) {}

	grafo<int> generar(bool casoPeor){
		grafo<int> g;
		srand(1);
		for(int i = 1; i < numVertices+1; i++){
			cout << "insertando vertice " << i << endl;
			g.insertarVertice(i);
		}

		for(int i = 1; i < numVertices+1; i++){
			cout << "arista para vertice " << i << endl;
			for(int j = 1; j < numVertices+1; j++){
				if(i != j){
					float coste = (int) rand() % coste_maximo;
					float pa = (casoPeor)? 0 : (float) rand() / RAND_MAX ;
					if(pa < prob_arista){
						g.crearArista(i,j,coste);
					}
				}
			}
		}

		return g;
	}
};

#endif /* GRAPH_GENERATOR_H_ */
