/*
 * skew_heap.h
 *
 *  Created on: 26 dic. 2020
 *      Author: Guille
 */

#ifndef SKEW_HEAP_H_
#define SKEW_HEAP_H_

#include<stdexcept>
using namespace std;

template <class T, class Comparator = std::less<T>>
class generic_skew_heap {

	struct Node;
	using Link = Node *;
	struct Node {
		T elem;
		Link iz,dr, pad;
		Node(T const & e, Link i = nullptr , Link d = nullptr, Link p = nullptr): elem(e),iz(i),dr(d),pad(p) {}

		bool operator== (Node const& other){
			return this->elem == other.elem;
		}
	};

	Link root;
	int elems;
	Comparator comp;

public:

	generic_skew_heap(Comparator c = Comparator()){
		root = nullptr;
		elems = 0;
		comp = c;

	}

	void insert(T e){
		if(root != nullptr){
			Link l = new Node(e);
			Link r = unir(l, root, root);
			root = r;
		}
		else{
			root = new Node(e);
		}
		elems++;
	}

	T borra_Min(){
		T e = this->root->elem;
		if(root->dr == nullptr && root->iz == nullptr){
			borra_Nodo(this->root);
			this->root = nullptr;
		}
		else{
			Link r = unir(root->iz, root->dr, root);
			borra_Nodo(this->root);
			this->root = r;
		}
		return e;
	}



	T min(){
		if (root != nullptr){
			return root->elem;
		}
		else{
			throw std::domain_error("Monticulo vacio");
		}
	}

	int getElems(){ return elems; }


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
			if(comp(a->elem, b->elem)){
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

	T borra(Link origen){
		if(origen != nullptr){
			T elem = origen->elem;
			Link i = origen->iz;
			Link d = origen->dr;
			Link p = origen->pad;

			bool lado;
			if(p->iz->elem == elem){lado = true;}
			else {lado = false;}
			borra_Nodo(origen);
			Link r = unir(i,d,p);
			if(lado){p->iz = r;}
			else{p->dr = r;}
			elems--;
			return elem;
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
