#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

typedef unsigned int uint;
typedef unsigned short ushort;

//1, 8, 3, 7, 2, 9, 4, 5, 6

template <class T>
struct Node{
	T data;
	Node<T>* sons[2];
	short height;
	ushort depth;
	Node(T x){
		sons[0] = sons[1] = 0;
		data = x;
		height = 0;
		depth = 0;
	}
};

template <class T>
void printList(list<Node<T>* > xd){
	for(typename list<Node<T>* >::iterator it = xd.begin(); it != xd.end(); it++){
		std::cout << (*it)->data << ' ';
	}
	std::cout << endl;
}

template <class T, class C>
class AVL{
public:
	Node<T>* root;
	C mc;
	AVL();
	bool find(T x, Node<T>**& p);
	bool insert(T x);
	bool remove(T x);
	//private:
	Node<T>** Rep(Node<T>** p);
	short getHeight(Node<T>* p);
	void printTree(Node<T>* , int space=0);
private:
	bool findInPath(Node<T>* p);
	bool findHeight(Node<T>**& p, short& h);
	void updateDepth();
	void updateDepthR();
	void updateHeights(T x);
	list< Node<T>* > path;
	void RR(Node<T>** p);
	void LL(Node<T>** p);
	void LR(Node<T>** p);
	void RL(Node<T>** p);
};

template <class T, class C>
bool AVL<T,C>::findInPath(Node<T>* p){
	for (typename list<Node<T>* >::iterator it = path.begin(); it != path.end(); it++){
		if ( *it == p ) return 1;
	}
	return 0;
}

template <class T, class C>
bool AVL<T,C>::findHeight(Node<T>**& p, short& h){
	for(typename list<Node<T>*>::reverse_iterator it = path.rbegin(); it != path.rend(); it++){
		if ((*it)->height == 2){
			p = &(*it);
			if ( (*it)->sons[1]->height == -1) h = 3;
			else h = 2;
			return 1;
		} else if ((*it)->height == -2){
			p = &(*it);
			if ( (*it)->sons[0]->height == 1) h = -3;
			else h = -2;
			return 1;
		}
	}
	return 0;
}

template <class T, class C>
void AVL<T,C>::RR(Node<T>** p){
	typename list<Node<T>*>::iterator it = path.end();
	bool LR = 0, RL = 0;
	if ( (*p)->sons[1] && (*p)->sons[1]->sons[1] && (*p)->sons[1]->sons[1]->height == -1) LR = 1;
	if ( (*p)->height  == 1) {RL = 1; LR = 0;}
	while ( (*it) != (*p) ){
		it--;
	}
	Node<T>* temp, *father;
	if (*it != root){ //si es que se tiene que balancear
		it--;
		if (RL){
			while( *p != (*it)->sons[0]) it--; //busca en el camino hasta encontrar el padre de p
			temp = *it;
		} else 
		//temp = *(--it); //fuera de la raiz
		temp = *(it);
	}
	Node<T>* gfather = *p;
	father = (*p)->sons[1];
	if (!findInPath(father) ) path.push_back(father);
	Node<T> *bl = father->sons[0];
	father->sons[0] = gfather;
	gfather->sons[1] = bl;
	if (root == gfather) root = father;
	else {
		if (father->data < temp->data ) temp->sons[0] = father;
		else temp->sons[1] = father;
	}
}

template <class T, class C>
void AVL<T,C>::LL(Node<T>** p){
	bool LR = 0, RL = 0;
	typename list<Node<T>*>::iterator it = path.end();
	if ((*p)->sons[0] && (*p)->sons[0]->sons[0] && (*p)->sons[0]->sons[0]->height == 1 ) RL = 1;
	if ( (*p)->height == -1) {LR = 1; RL = 0;}
	while ( (*it) != (*p)){
		it--;
	}
	Node<T>* temp, *father;
	if (*it != root){ //si es que se tiene que balancear
		--it;
		if (LR){
			while( *p != (*it)->sons[1]) it--; //busca en el camino hasta encontrar el padre de p
			temp = *it;
		} else 
		temp = (*it);
	}
	Node<T>* gfather = *(p);
	father = (*p)->sons[0];
	Node<T> *br = father->sons[1];
	if (!findInPath(father) ) path.push_back(father);
	father->sons[1] = gfather;
	gfather->sons[0] = br;
	if (root == gfather){
		root = father;
	}
	else {
		if (father->data > temp->data) temp->sons[1] = father;
		else temp->sons[0] = father;
	}
}

template <class T, class C>
void AVL<T,C>::LR(Node<T>** p){
	if (!findInPath( (*p)->sons[1] ) ) path.push_back((*p)->sons[1]);
	LL( &(*p)->sons[1]);
	RR(p);
}

template <class T, class C>
void AVL<T,C>::RL(Node<T>** p){
	if (!findInPath( (*p)->sons[0] ) ) path.push_back((*p)->sons[0]);
	RR( &(*p)->sons[0]);
	LL(p);
}

template <class T, class C>
Node<T>** AVL<T,C>::Rep(Node<T>** p){
	for(p = &(*p)->sons[0]; *p && (*p)->sons[1]; p = &(*p)->sons[1]){ //the university-one like
		path.push_back(*p);
	}
	path.push_back(*p);
	return p;
}

template <class T, class C>
short AVL<T,C>::getHeight(Node<T>* p){
	//if (p->data == x) return 0;
	short left, right;
	if (p->sons[0]) left = (p)->sons[0]->depth;
	else return (p->depth);//left = 0;
	if (p->sons[1]) {
		right = p->sons[1]->depth;
	}
	else return -p->depth;//right = 0;
		return right - left;
}

template <class T, class C>
void AVL<T,C>::updateHeights(T x){
	for(typename list<Node<T>* >::iterator it = path.begin(); it != path.end(); it++){
		(*it)->height = getHeight(*it);
	}
}

template <class T, class C>
void AVL<T,C>::updateDepth(){
	Node<T>** p;
	bool balance = 0;
	ushort lDepth, rDepth;
	typename list<Node<T>* >::reverse_iterator rit = path.rbegin();
	while(rit != path.rend() ){
		if ( !(*rit)->sons[0] && !(*rit)->sons[1] ){
			(*rit)->depth = 0;
			rit++;
			continue;
		}
		if ( (*rit)->sons[0] ) lDepth = (*rit)->sons[0]->depth;
		else lDepth = 0;
		if ( (*rit)->sons[1] ) rDepth = (*rit)->sons[1]->depth;
		else rDepth = 0;
		(*rit)->depth = max(lDepth, rDepth) + 1;
		(*rit)->height = getHeight(*rit);
		if ((*rit)->height == 2){
			p = &(*rit);
			balance = 1;
			if ( getHeight((*rit)->sons[1]) == -1){
				LR(p);
			}
			else{
				RR(p);
			}
		} else if ((*rit)->height == -2){
			p = &(*rit);
			balance = 1;
			if ( getHeight((*rit)->sons[0]) == 1){
				RL(p);
			}
			else{
				LL(p);
			}
		}
		if (balance){
			break;
		}
		rit++;
	}
}

template <class T, class C>
void AVL<T,C>::updateDepthR(){
	ushort lDepth, rDepth;
	typename list<Node<T>* >::iterator it = path.begin();
	while(it != path.end() ){
		if ( !(*it)->sons[0] && !(*it)->sons[1] ){
			(*it)->depth = 0;
			it++;
			continue;
		}
		if ( (*it)->sons[0] ) lDepth = (*it)->sons[0]->depth;
		else lDepth = 0;
		if ( (*it)->sons[1] ) rDepth = (*it)->sons[1]->depth;
		else rDepth = 0;
		(*it)->depth = max(lDepth, rDepth) + 1;
		(*it)->height = getHeight(*it);
		it++;
	}
}


template <class T, class C>
AVL<T,C>::AVL(){
	this->root = 0;
}

template <class T, class C>
bool AVL<T,C>::find(T x, Node<T>**& p){
	for(p = &root; *p && (*p)->data != x; p = &((*p)->sons[mc((*p)->data, x)])){
		path.push_back(*p);
	}
	return !!*p;
}

template <class T, class C>
bool AVL<T,C>::insert(T x){
	Node<T>** p;
	if(find(x, p)){
		path.clear();
		return 0;
	}
	*p = new Node<T>(x);
	path.push_back(*p);
	updateDepth();
	updateDepthR();
	path.clear();
	return 1;
}

template<class T, class C>
bool AVL<T,C>::remove(T x){
	Node<T>** p;
	if(!(find(x,p))){
		path.clear();
		return 0;
	}
	path.push_back(*p);
	if ((*p)->sons[0] && (*p)->sons[1]){
		Node<T>** q = Rep(p);
		(*p)->data = (*q)->data;
		p = q;
	}
	Node<T>* temp = *p;
	*p = (*p)->sons[(*p)->sons[1]!=0];
	delete temp;
	path.pop_back();
	updateDepth();
	updateDepthR(); //this is needed when we do a balance after erasing
	path.clear(); //because a balanced node may not be a part of the path
	return 1;
}

template<class T, class C>
void AVL<T,C>:: printTree(Node<T>* root_, int space) {
  if(root_ == NULL) {
    return;
  }
  space += 10;
  printTree(root_->sons[1], space);
  
  std::cout<<std::endl;
  for(int i = 10; i < space; i++) {
    std::cout<<" ";
  }
  
  std::cout<< root_->data<<std::endl;
  printTree(root_->sons[0], space);
}

/* MAIN SETUP PANEL */

/*
#include "avlTree.hpp"

using namespace std;

template <class T>
class Menor{
	public:
		inline bool operator()(T a, T b){
			return a<b;
		}
};


int main() {
	AVL<int, Menor <int> > test;

	int option, n;
	while (true) {
		std::cout << " |***************** Arbol AVL *****************| " << std::endl;
		std::cout << " |* Presiona (1) Para Insertar un nodo        *| " << std::endl;
		std::cout << " |* Presiona (2) Para Eliminar un nodo        *| " << std::endl;
		std::cout << " |* Presiona (0) Para Salir del Programa      *| " << std::endl;
		std::cout << " |*********************************************| " << std::endl;
		std::cin >> option;
		if (option == 1) {
			while (true) {
				std::cout << "\n\n Presiona (0) para volver al menu anerior, ingrese un numero: " << std::endl;
				std::cin >> n;
				if (n == 0)
					break;
				test.insert(n);
				test.printTree(test.root);
			}
		}
		else if (option == 2) {
			std::cout << "\n\n Presiona (0) para volver al menu anterior, borrar el numero: " << std::endl;
			std::cin >> n;
			test.remove(n);
			test.printTree(test.root);
		}
		else if (option == 0)
			break;
	}

	return 0;
}
*/