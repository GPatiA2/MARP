/*
 * skew_heap.h
 *
 *  Created on: 26 dic. 2020
 *      Author: Guille
 */

#ifndef SKEW_HEAP_H_
#define SKEW_HEAP_H_

#include<unordered_map>
#include<stdexcept>
using namespace std;

using clave = int;
using valor = int;
class skew_heap {

	struct Node;
	using Link = Node *;
	struct Node {
		clave c;
		valor v;
		Link iz,dr, pad;
		Node(int clave, int valor, Link i = nullptr , Link d = nullptr, Link p = nullptr): c(clave), v(valor) ,iz(i),dr(d),pad(p) {}

		bool operator== (Node const& other){
			return this->c == other.c && this->v == other.v;
		}

		bool operator< (Node const& other){
			return this->v < other.v;
		}
	};

	Link root;
	int cont;
	unordered_map<clave, Link> * mapa;

public:

	skew_heap(){
		root = nullptr;
		cont = 0;
		mapa = new unordered_map<int, Link>;
	}

	void clear(){
		mapa->clear();
		liberaNodos(root);
		cont = 0;
		root = nullptr;
	}

	void insert(clave c, valor v){
		if(root != nullptr){
			Link l = new Node(c,v);
			Link r = unir(l, root, root);
			root = r;
			mapa->insert({c, l});
		}
		else{
			root = new Node(c,v);
			mapa->insert({v, root});
		}
		cont++;
	}

	pair<clave,valor> borra_Min(){
		pair<clave,valor> e = std::make_pair(this->root->c, this->root->v);
		if(root->dr == nullptr && root->iz == nullptr){
			borra_Nodo(this->root);
			this->root = nullptr;
		}
		else{
			Link r = unir(root->iz, root->dr, root);
			borra_Nodo(this->root);
			this->root = r;
		}
		mapa->erase(e.first);
		cont--;
		return e;
	}

	bool contains(clave c){
		return mapa->count(c);
	}

	void decrease_key(clave c, valor vn){
		auto it = mapa->find(c);
		if(it != mapa->end()){
			Link l = it->second;
			if(l->v > vn){
				if(l->pad->iz == l){
					l->pad->iz = nullptr;
					l->pad = nullptr;
				}
				else{
					l->pad->dr = nullptr;
					l->pad = nullptr;
				}

				l->v = vn;

				Link r = unir(root,l,root);
				root = r;
			}
			else{
				throw domain_error("Intentas cambiar un valor por otro mayor");
			}
		}
		else{
			throw domain_error("La clave no se encuentra en el monticulo");
		}

	}

	void sacaElementos() const {
		cout<< "Hay " << mapa->size() << " ventos en el mapa" << endl;
		cout<< "Hay " << cont << " ventos en el monticulo " << endl;
		for(auto e: *mapa){
			cout << "Clave = " <<  e.second->c << " Valor = "<< e.second->v << "  "<< endl;
		}
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
		liberaNodos(root);
		delete mapa;
	}

protected:

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
			if(a->v < b->v){
				Link ader = a->dr;
				a->dr = a->iz;
				a->iz = unir(ader,b, a);
				a->pad = p;
				return a;
			}
			else{
				Link bder = b->dr;
				b->dr = b->iz;
				b->iz = unir(a, bder, b);
				b->pad = p;
				return b;
			}
		}
	}
private:


	void liberaNodos(Link l){
		if(l != nullptr){
			liberaNodos(l->dr);
			liberaNodos(l->iz);
			this->borra_Nodo(l);
		}
	}

	int borra(Link origen){
		if(origen != nullptr){
			int v = origen->v;
			Link i = origen->iz;
			Link d = origen->dr;
			Link p = origen->pad;

			bool lado;
			if(p->iz == origen){lado = true;}
			else {lado = false;}

			borra_Nodo(origen);

			Link r = unir(i,d,p);
			if(lado){p->iz = r;}
			else{p->dr = r;}
			cont--;
			return v;
		}
		else{
			throw std::domain_error("Monticulo vacio");
		}
	}

	static void libera(Link a){
		if(a != nullptr){
			libera(a->iz);
			libera(a->dr);
			delete a;
		}
	}

	static void borra_Nodo(Link a){
		if (a != nullptr) { delete a; }
	}
};



#endif /* SKEW_HEAP_H_ */
