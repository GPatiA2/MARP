/*
 * Guillermo Garcia Patiño Lenza
 * MAR Grupo A
 * skew_heap.h
 */
#ifndef SKEW_HEAP_H_
#define SKEW_HEAP_H_

#include<unordered_map>
#include<stdexcept>
using namespace std;


/*
 * Esta clase implementa los monticulos sesgados
 * Puede hacerse generica, pero se han empleado claves y valores enteros
 * 	para simplificar la implementacion
 *
 * Contiene:
 *   1- un arbol binario al que se accede por su raiz 'root'
 *   2- un entero que tiene el valor del numero de elementos del monticulo
 *   3- un mapa (clave-puntero a nodo) que permite encontrar el nodo en el que se encuentra una
 *         clave en tiempo constante
 */

using clave = int;
using valor = int;

class skew_heap {

	/*
	 * Este Struct representa un nodo del monticulo sesgado
	 * Se incluyen punteros al padre para facilitar el decreaseKey
	 *
	 * Se renombra el puntero a este struct como Link
	 */
	struct Node;
	using Link = Node *;
	struct Node {
		clave c;
		valor v;
		Link iz,dr, pad;
		Node(int clave, int valor, Link i = nullptr , Link d = nullptr, Link p = nullptr): c(clave), v(valor) ,iz(i),dr(d),pad(p) {}

		bool operator== (Node const& other){
			return this->c == other.c;
		}

		bool operator< (Node const& other){
			return this->v < other.v;
		}
	};

	Link root;
	int cont;
	unordered_map<clave, Link> mapa;

public:

	skew_heap(){
		root = nullptr;
		cont = 0;
		mapa = {};
	}

	/*
	 * Este metodo borra el contenido del monticulo
	 */
	void clear(){
		mapa.clear();
		libera(root);
		cont = 0;
		root = nullptr;
	}

	/*
	 * Metodo que inserta la clave 'c' con valor 'v' en el monticulo
	 * Como se ha visto en clase, se crea un monticulo sesgado con un solo elemento y
	 * 	se une al monticulo principal para insertarlo
	 */
	void insert(clave c, valor v){
		if(root != nullptr){
			Link l = new Node(c,v);
			Link r = unir(l, root, root);
			root = r;
			mapa.insert({c, l});
		}
		else{
			root = new Node(c,v);
			mapa.insert({c, root});
		}
		cont++;
	}

	bool empty() const {return cont == 0 ; }

	/*
	 * Este metodo borra el elemento minimo del monticulo, que se encuentra en
	 * 	la raiz, y devuelve el par (clave, valor) que lo representaba.
	 *
	 * Distingue entre 2 casos:
	 *   1- Si solo hay un elemento, se limita a borrar el nodo que lo contiene
	 *   		y ajustar los punteros necesarios
	 *
	 *   2- Si hay mas de un elemento, descuelga el hijo izquierdo y el hijo derecho
	 *   		de la raiz. Borra la raiz, y apunta el puntero de la raiz a la raiz del
	 *   		monticulo resultante de la union de ambos hijos
	 */
	pair<clave,valor> borra_Min(){

		pair<clave,valor> e = std::make_pair(this->root->c, this->root->v);
		if(mapa.erase(e.first)){
			if(root->dr == nullptr && root->iz == nullptr){
				borra_Nodo(this->root);
				this->root = nullptr;
			}
			else{
				Link l = root->iz;
				Link r = root->dr;

				root->iz = nullptr;
				root->dr = nullptr;
				if(l != nullptr){l->pad = nullptr;}
				if(r != nullptr){r->pad = nullptr;}

				borra_Nodo(this->root);
				root = nullptr;

				root = unir(l, r, nullptr);
				root->pad = root;

			}
			cont--;
			return e;
		}
		else{
			string s = "Se intenta borrar " + std::to_string(e.first) + " que no esta en el monticulo ";
			throw domain_error(s);
		}
	}

	/*
	 * Metodo que consulta si una clave se encuentra en el monticulo
	 */
	bool contains(clave c) const {
		return mapa.find(c) != mapa.end();
	}

	/*
	 * Metodo que decrece una clave y le asigna el valor vn
	 * Esencialmente, el funcionamiento del metodo consiste en:
	 * 	1- Descolgar el nodo que se va a decrecer del arbol original
	 * 	2- Decrecer la clave del del nodo que se ha descolgado
	 * 	3- Unir el monticulo original con el arbol que se ha descolgado
	 *
	 * Ademas, en caso de que el nodo a decrecer sea la raiz, simplemente
	 * 	decrece la clave que hay en ese nodo, ahorrando los pasos restantes
	 *
	 * De esta manera, la operacion pasa a estar en O(lg n) donde n son los elementos
	 *  actuales del montículo, ya que se accede en tiempo constante al nodo de la clave que
	 *  se quiere decrecer.
	 */
	void decrease_key(clave c, valor vn){
		auto it = mapa.find(c);
		if(it != mapa.end()){
			//Obtengo un puntero al nodo que almacena la clave a decrecer
			Link l = it->second;
			if(l == root){ root -> v =  vn ;}
			else{
				if(l->v > vn){
					//Descuelgo el nodo que tiene la clave que quiero decrecer del
					// monticulo principal
					if(l->pad->iz == l){
						l->pad->iz = nullptr;
						l->pad = nullptr;
					}
					else{
						l->pad->dr = nullptr;
						l->pad = nullptr;
					}
					//Decrezco la clave
					l->v = vn;
					//Uno los dos montículos que quedan
					Link r = unir(root,l,root);
					root = r;
				}
				else{
					throw domain_error("Intentas cambiar un valor por otro mayor");
				}
			}
		}
		else{
			throw domain_error("La clave no se encuentra en el monticulo");
		}

	}

	/*
	 * Metodo que permite consultar todos los elementos del monticulo
	 */
	string sacaElementos() const {
		string s = "";
		s+= "Hay " + std::to_string( mapa.size() ) + " elementos en el mapa \n";
		s+= "Hay " + std::to_string( cont ) +  " elementos en el monticulo \n" ;
		for(auto e: mapa){
			s+= "Clave = " + std::to_string( e.first ) + " Valor = " + std::to_string( e.second->v ) + " \n ";
		}
		return s;
	}


	pair<clave,valor> min() const {
		if (root != nullptr){
			return pair<clave,valor>(root->c,root->v);
		}
		else{
			throw std::domain_error("Monticulo vacio");
		}
	}

	int getElems() const { return cont; }

	~skew_heap(){
		libera(root);
	}

protected:
	/*
	 * Metodo auxiliar para consultar el arbol del monticulo en preorden
	 */
	string preorden(Link l) const {
		if(l == nullptr) return "";
		string s = "(" + std::to_string(l->c) + " " + std::to_string(l->v) + ") ";
		string s1 = preorden(l->iz);
		string s2 = preorden(l->dr);
		return (s + s1 + s2);
	}

	/*
	 * Metodo para unir dos nodos a y b .
	 * La raiz del monticulo resultante de esa union acabara
	 * 		siendo hijo del nodo p
	 *
	 *  El coste de esta operación tiene un coste amortizado O(lg n)
	 */
	Link unir(Link a, Link b, Link p){
 		if(a == nullptr){
 			b->pad = p;
			return b;
		}
		else if(b == nullptr){
			a->pad = p;
			return a;
		}
		else{
			if(b->v < a->v){
				Link tmp = a;
				a = b;
				b = tmp;
			}
			Link tmp2 = a->iz;
			a->iz = a->dr;
			a->dr = tmp2;
			a->iz = unir(a->iz,b,a);
			a->pad = p;
			return a;
		}
	}

private:

	/*
	 * En la parte privada solo se incluyen los diferentes metodos que se emplean para
	 * 	eliminar nodos del arbol.
	 *
	 *
	 * libera : borra todos los nodos que estan por debajo del nodo L y al propio nodo
	 * 				tambien
	 *
	 * borra_Nodo : borra el nodo que recibe como parametro, devolviendo la memoria que ocupaba
	 */


	static void libera(Link a){
		if(a != nullptr){
			libera(a->iz);
			libera(a->dr);
			delete a;
		}
	}

	static void borra_Nodo(Link a){
		if (a != nullptr) {
		delete a; }
	}
};



#endif /* SKEW_HEAP_H_ */
