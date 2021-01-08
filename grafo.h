
#ifndef GRAFO_H_
#define GRAFO_H_

#include <unordered_map>
#include <unordered_set>
#include <list>
#include <stdexcept>
using namespace std;

template <class T>
class grafo{

public:
	using coste = int;
	using vertice = T;

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

	void insertarVertice(vertice const & v){
		vertices.insert(v);
		if(aristas.count(v) == 0){
			aristas[v] = new list<gnode>;
		}
	}

	const list<gnode> adyacentes(vertice const & v) const {
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

	const unordered_set<vertice> & vertSet () const {
		return this->vertices;
	}

	void crearArista(vertice origen, vertice destino, int c){
		insertarArista(origen, destino, c);
		n_aristas++;
	}

	vertice getFirst() const {
		if(!vertices.empty()){
			return *vertices.begin();
		}
		else{
			throw domain_error("No hay vertices en el grafo");
		}
	}

	int getNumVertices() const { return vertices.size(); }

	string print() const {
		string s;
		for(auto v : vertices){
			string vlist = std::to_string(v);
			vlist += " ";
			for(gnode gn : *aristas.at(v)){
				vlist += "(" + std::to_string(gn->vert) + " , " + std::to_string(gn->cost) + " ) ,";
			}
			s += vlist;
			s += '\n';
		}
		return s;
	}

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
