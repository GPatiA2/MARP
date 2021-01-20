/*
 * Guillermo Garcia Patiño Lenza
 * MAR Grupo A
 * graph_generator.h
 */

#ifndef GRAPH_GENERATOR_H_
#define GRAPH_GENERATOR_H_

#include <stdlib.h>
#include "grafo.h"

using namespace std;

class graph_generator{

	int numVertices;
	float prob_arista;
	int coste_maximo;

public:

	graph_generator(int nv, float a, int cM) : numVertices(nv), prob_arista(a), coste_maximo(cM) {}

	/*
	 * Este metodo vale para cambiar el numero de vertices del grafo que genera esta clase
	 */
	void setNumVertices(int v){ numVertices = v;}

	/*
	 * Para generar el grafo se insertan primero los vertices.
	 * Despues, para cada vertice, se inerta en el grafo una arista con cada uno de los vertices restantes
	 * 	teniendo en cuenta si estoy generando o no un grafo que provoca uno de los peores casos de Dijkstra
	 * 	(casoPeor = True) o no (casoPeor = False)
	 */
	grafo<int> generar(bool casoPeor){
		grafo<int> g;
		srand(time(NULL));
		for(int i = 1; i < numVertices+1; i++){
			g.insertarVertice(i);
		}

		for(int i = 1; i < numVertices+1; i++){
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
