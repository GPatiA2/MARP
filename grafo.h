/*
 * Guillermo Garcia Patiño Lenza
 * MAR Grupo A
 * grafo.h
 */
#ifndef GRAFO_H_
#define GRAFO_H_

#include <unordered_map>
#include <unordered_set>
#include <list>
#include <stdexcept>
using namespace std;


/*
 * Esta clase representa el grafo como un conjunto de vertices
 * 	y la lista de adyacencia de cada uno
 */
template <class T>
class grafo{

public:
	using coste = int;
	using vertice = T;

	/*
	 * Struct que sirve para guardar un vertice en una de las listas de adyacencia del
	 * grafo. Junto al vertice, se guarda el coste de la arista hasta el.
	 */
	struct node {
		vertice vert;
		coste cost;
		node(vertice vert, coste cost) : vert(vert), cost(cost) {}
	};
	using gnode = node*;

protected:

	unordered_set<vertice> vertices;
	unordered_map<vertice, list<gnode> *> aristas;

	int n_aristas;

public:



	grafo(){
		vertices = {};
		aristas = {};
		n_aristas = 0;
	}

	~grafo(){
		for(auto p : aristas){
            auto it = p.second->rbegin();
            while(it != p.second->rend()){
                delete *it;
                it ++;
            }
			delete p.second;
		}
	}

	/*
	 * Para insertar un vertice en el grafo, lo inserto en
	 * 	el conjunto de vertices y creo una lista de adyacencia para
	 * 	el
	 */
	void insertarVertice(vertice const & v){
		vertices.insert(v);
		if(aristas.count(v) == 0){
			aristas[v] = new list<gnode>;
		}
	}

	/*
	 * Metodo que obtiene la lista de adyacencia para un vertice
	 * 	determinado.
	 * Devuelve una referencia constante a la lista que almacena el grafo
	 * 	para no ocupar mas memoria de la necesaria.
	 */
	const list<gnode> & adyacentes(vertice const & v) const {
		list<gnode> ady;
		auto it = aristas.find(v);
		if(it != aristas.end()){
			const list<gnode> & l = *it->second;
			return l;
		}
		else{
			throw domain_error("Este vertice no se encuentra en el grafo");
		}
	}

	/*
	 * Metodo que permite acceder al conjunto de vertices del grafo.
	 */
	const unordered_set<vertice> & vertSet () const {
		return this->vertices;
	}

	/*
	 * Metodo para insertar una arista desde el vertice origen hasta
	 * 	el vertice destino con coste c
	 */
	void crearArista(vertice origen, vertice destino, int c){
		insertarArista(origen, destino, c);
		n_aristas++;
	}

	/*
	 *	Este metodo simplemente devuelve el primer vertice del
	 *		conjunto. No tiene mas utilidad que proporcionar al
	 *		algoritmo de Dijkstra un vertice por donde empezar
	 */
	vertice getFirst() const {
		if(!vertices.empty()){
			return *vertices.begin();
		}
		else{
			throw domain_error("No hay vertices en el grafo");
		}
	}

	int getNumVertices() const { return vertices.size(); }

	/*
	 * Metodo auxiliar que permite visualizar las listas de
	 *  adyacencia para cada vertice
	 */
	string print() const {
		string s;
		for(auto v : vertices){
			string vlist = std::to_string(v);
			vlist += " ";
			for(gnode gn : *aristas.at(v)){
				vlist += "(" + std::to_string(gn->vert) + " , " + std::to_string(gn->cost) + " ) ,";
			}
			vlist.resize(vlist.size()-1);
			s += vlist;
			s += '\n';
		}
		return s;
	}

	/*
	 * Metodo auxiliar que permite visualizar el grafo como
	 *   una matriz de adyacencia
	 */
	string adyMat() const {
		bool mat[vertices.size()][vertices.size()];
		for(unsigned int i = 0; i < vertices.size(); i++){
			for(unsigned int j = 0; j < vertices.size(); j++){
				mat[i][j] = false;
			}
		}
		for(auto v : vertices) {
			for(gnode gn : *aristas.at(v)){
				mat[v-1][gn->vert-1] = true;
			}
		}
		string s;
		for(unsigned int i = 0; i < vertices.size(); i++){
			string fila = "";
			for(unsigned int j = 0; j < vertices.size(); j++){
				if(j == vertices.size() - 1){
					if(mat[i][j]){
						fila += "1";
					}
					else{
						fila += "0";
					}
				}
				else{
					if(mat[i][j]){
						fila += "1, ";
					}
					else{
						fila += "0, ";
					}
				}
			}
			s += fila;
			s += '\n';
		}
		return s;
	}
protected:

	/*
	 * Metodo que recibe los datos de una arista, la crea y la inserta donde
	 * es necesario.
	 */
	void insertarArista(vertice origen, vertice destino, coste c){

		auto it = aristas.find(origen);
		if( it != aristas.end()){
			auto & lista = it->second;
			lista->push_back(new node(destino,c));
		}
		else{
			throw domain_error("Para insertar esta arista, primero inserta el vertice de origen");
		}
	}

};

#endif /* GRAFO_H_ */
