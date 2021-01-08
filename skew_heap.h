
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

	void clear(){
		mapa.clear();
		liberaNodos(root);
		cont = 0;
		root = nullptr;
	}

	void insert(clave c, valor v){
		if(!mapa.count(c)){
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
		else{
			throw domain_error("Esta clave ya se encuentra en el monticulo");
		}
	}

	bool empty() const {return cont == 0 ; }

	pair<clave,valor> borra_Min(){

//		cout << "Borrando " << endl;


		pair<clave,valor> e = std::make_pair(this->root->c, this->root->v);
		if(mapa.erase(e.first)){
			if(root->dr == nullptr && root->iz == nullptr){
				cout << "CASO 1" << endl;
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
//				cout << "Voy a borrar " << endl;
//				cout << preorden(root) << endl;
				borra_Nodo(this->root);
				root = nullptr;
				root = unir(l, r, nullptr);
				root->pad = root;
//				cout << preorden(root) << endl;
//				cout << "Borrado" << endl;
			}
			cont--;
			return e;
		}
		else{
			string s = "Se intenta borrar " + std::to_string(e.first) + " que no esta en el monticulo ";
			throw domain_error(s);
		}
	}

	bool contains(clave c) const {
		return mapa.find(c) != mapa.end();
	}

	void decrease_key(clave c, valor vn){
//		sacaElementos();
		auto it = mapa.find(c);
		if(it != mapa.end()){
			Link l = it->second;
			if(l == root){ root -> v =  vn ;}
			else{
				if(l->v > vn){
//					cout << "Voy a decrecer " << c << " " << l->v << " a " << vn << endl;
//					cout << " a = " << ((root == nullptr)? "Vacio" : std::to_string(root->c) + " " + std::to_string(root->v)) << endl;
//					cout << " b = " << l->c << " " << l->v << endl;
//					cout << preorden(root) << endl;
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
//					cout << preorden(root) << endl;
//					cout << "Decrecido" << endl;
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

	void sacaElementos() const {
		cout<< "Hay " << mapa.size() << " ventos en el mapa" << endl;
		cout<< "Hay " << cont << " ventos en el monticulo " << endl;
		for(auto e: mapa){
			cout << "Clave = " <<  e.first << " Valor = "<< e.second->v << "  "<< endl;
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
	}

protected:

	string preorden(Link l){
		if(l == nullptr) return "";
		string s = "(" + std::to_string(l->c) + " " + std::to_string(l->v) + ") ";
		string s1 = preorden(l->iz);
		string s2 = preorden(l->dr);
		return (s + s1 + s2);
	}

	Link unir(Link a, Link b, Link p){
 		if(a == nullptr){
// 			cout << "Caso 1" << endl;
 			b->pad = p;
			return b;
		}
		else if(b == nullptr){
//			cout << "Caso 2" << endl;
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
//			if( a != nullptr && (b == nullptr || a->v < b->v )){
////				cout << "Caso 3" << endl;
//				Link ader = a->dr;
//				a->dr = a->iz;
//				a->iz = unir(ader,b, a);
//				a->iz->pad = a;
//				a->pad = p;
//				return a;
//			}
//			else{
////				cout << "Caso 4" << endl;
//				Link bder = b->dr;
//				b->dr = b->iz;
//				b->iz = unir(a, bder, b);
//				b->iz->pad = b;
//				b->pad = p;
//				return b;
//			}
//		if(a == nullptr && b == nullptr){ return nullptr; }
//		else{
//			if( a != nullptr && (b == nullptr || a->v < b->v )){
////				cout << "Caso 3" << endl;
//				Link ader = a->dr;
//				a->dr = a->iz;
//				a->iz = unir(ader,b, a);
//				a->pad = p;
//				return a;
//			}
//			else{
////				cout << "Caso 4" << endl;
//				Link bder = b->dr;
//				b->dr = b->iz;
//				b->iz = unir(a, bder, b);
//				b->pad = p;
//				return b;
//			}
//		}
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
		if (a != nullptr) {
//			cout << "Borro nodo con elem " << a->c << endl;
		delete a; }
	}
};



#endif /* SKEW_HEAP_H_ */
