/*
 * skew_heap2.h
 *
 *  Created on: 26 dic. 2020
 *      Author: Guille
 */

#ifndef SKEW_HEAP2_H_
#define SKEW_HEAP2_H_

#include <unordered_map>
#include <stdexcept>
#include <iostream>
using namespace std;

template <class T, class Comparator = std::less<T>>
class generic_skew_heap2 {

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
	unordered_map<const T *, Link> mapa;

public:

	generic_skew_heap2(Comparator c = Comparator()){
		root = nullptr;
		elems = 0;
		comp = c;
		mapa = {};
	}

	void insert(T e){
		if(root != nullptr){
			Link l = new Node(e);
			Link r = unir(l, root, root);
			mapa[&e] = l;
			root = r;
		}
		else{
			root = new Node(e);
			mapa[&e] = root;
		}
		elems++;
	}

	T borra_Min(){
		T e = borra(this->root);
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

	void decreaseKey (T k1 , T k2) {
		if(comp(k2,k1)){
			decrecer(k1, k2);
		}
		else{
			throw domain_error("Intentas cambiar una clave por otra mayor");
		}
	}

	void elementos(){
		for(auto e : mapa){
			cout << e.second->elem << endl;
		}
	}

protected:

	void decrecer(T const & k1, T const & k2){
		try{
			Link o = mapa.at(&k1);
			T e = borra(o);
			mapa.erase(&e);

			insert(k2);
		}
		catch (out_of_range & oor){
			throw domain_error("Intentas cambiar una clave que no existe");
		}
	}

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





#endif /* SKEW_HEAP2_H_ */
