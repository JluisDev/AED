#include <iostream>
#include <list>
using namespace std;

template <class T>
struct CNode{
	T m_x;
	CNode<T>* m_nodes[2];
	bool colour; //0 = red, 1 = black
	CNode(T x){
		m_nodes[0] = m_nodes[1] = 0;
		m_x = x;
		colour = 0;
	}
};

template <class T>
struct Menor{
	inline bool operator()(T a, T b){
		return a<b;
	}
};

template <class T, class C>
class RedBlack{
public:
	CNode<T>* m_root;
	RedBlack();
	bool find(T x, CNode<T>**& p);
	bool insert(T x);
	bool remove(T x);
	void inorder(CNode<T>* p);
	void printTree(CNode<T>* p);
private:
	CNode<T>** Rep(CNode<T>** p);
	C mc;
	list<CNode<T>* > path;
	void RU(CNode<T>* uncle, CNode<T>* father, CNode<T>* gfather); //Red Uncle
	void BUT(CNode<T>* p); //Black Uncle Triangular
	void BUL(CNode<T>* p); //Black Uncle Linear
	void LL(CNode<T>* father, CNode<T>* gfather, CNode<T>* temp); //Simlar to LL in AVL
	void RR(CNode<T>* father, CNode<T>* gfather, CNode<T>* temp); //Similar to RR in AVL
	void LR(CNode<T>* father, CNode<T>* gfather, CNode<T>* temp); //Similar to RL in AVL
	void RL(CNode<T>* father, CNode<T>* gfather, CNode<T>* temp); //Similar to LR in AVL
	void findCase(CNode<T>* p);
};

template <class T, class C>
CNode<T>** RedBlack<T,C>::Rep(CNode<T>** p){
	for(p = &(*p)->m_nodes[0]; *p && (*p)->m_nodes[1]; p = &(*p)->m_nodes[1]);
	return p;
}

template <class T, class C>
RedBlack<T,C>::RedBlack(){
	this->m_root = 0;
}

template <class T, class C>
void RedBlack<T,C>::findCase(CNode<T>* p){
	if (p == m_root){
		p->colour = 1;
		return;
	}
	typename list<CNode<T>* >::reverse_iterator it;
	for(it = path.rbegin(); *it != p; it++);
	CNode<T>* gfather, *father, *uncle, *temp = 0;
	if (++it == path.rend()) return; //no father
	father = (*it++);
	if (it == path.rend()) return; //no grand father
	gfather = (*it);
	if (*it != m_root ){
		temp = (*++it);
		it--;
	}
	if (gfather->m_nodes[0] == father) uncle = gfather->m_nodes[1];
	else uncle = gfather->m_nodes[0];
	if (uncle && !uncle->colour){
		RU(uncle, father, gfather);
		return;
	}
	if (!uncle){ //LL or RR
		if (father == gfather->m_nodes[0]){
			if (!father->m_nodes[0]){
				RL(father, gfather, temp);
				return;
			}
			LL(father, gfather, temp);
			father->colour = 1;
			father->m_nodes[1]->colour = 0;
		}
		else{
			if (!father->m_nodes[1]){
				LR(father, gfather, temp);
				return;
			}
			RR(father, gfather, temp);
			father->colour = 1;
			father->m_nodes[0]->colour = 0;
		}
		return;
	}
}

template <class T, class C>
void RedBlack<T,C>::RU(CNode<T>* uncle, CNode<T>* father, CNode<T>* gfather){
	uncle->colour = 1;
	father->colour = 1;
	if (gfather != m_root) gfather->colour = 0;
	else gfather->colour = 1;
}

template <class T, class C>
void RedBlack<T,C>::LL(CNode<T>* father, CNode<T>* gfather, CNode<T>* temp){
	CNode<T> *br = father->m_nodes[1];
	father->m_nodes[1] = gfather;
	gfather->m_nodes[0] = br;
	if (m_root == gfather){
		m_root = father;
	}
	else {
		temp->m_nodes[1] = father;
	}
	return;
}

template <class T, class C>
void RedBlack<T,C>::RR(CNode<T>* father, CNode<T>* gfather, CNode<T>* temp){
	CNode<T> *bl = father->m_nodes[0];
	father->m_nodes[0] = gfather;
	gfather->m_nodes[1] = bl;
	if (m_root == gfather){
		m_root = father;
	}
	else {
		temp->m_nodes[0] = father;
	}
}

template <class T, class C>
void RedBlack<T,C>::LR(CNode<T>* father, CNode<T>* gfather, CNode<T>* temp){
	LL(father->m_nodes[0], father, gfather);
	gfather->m_nodes[1]->colour = 1;
	gfather->colour = 0;
	RR(gfather->m_nodes[1], gfather, temp);
}

template <class T, class C>
void RedBlack<T,C>::RL(CNode<T>* father, CNode<T>* gfather, CNode<T>* temp){
	RR(father->m_nodes[1], father, gfather);
	gfather->m_nodes[0]->colour = 1;
	gfather->colour = 0;
	LL(gfather->m_nodes[0], gfather, temp);
}

template <class T, class C>
bool RedBlack<T,C>::find(T x, CNode<T>**& p){
	for(p = &m_root; *p && (*p)->m_x != x; p = &((*p)->m_nodes[mc((*p)->m_x, x)])){
		path.push_back(*p);
	}
	return !!*p;
}

template <class T, class C>
bool RedBlack<T,C>::insert(T x){
	CNode<T>** p;
	if(find(x, p)) return 0;
	*p = new CNode<T>(x);
	path.push_back(*p);
	/*if (*p == this->m_root)
		(*p)->colour = 1;*/
	findCase(*p);
	path.clear();
	return 1;
}

template<class T, class C>
bool RedBlack<T,C>::remove(T x){
	CNode<T>** p;
	if(!(find(x,p))) return 0;
	if ((*p)->m_nodes[0] && (*p)->m_nodes[1]){
		CNode<T>** q = Rep(p);
		(*p)->m_x = (*q)->m_x;
		p = q;
	}
	CNode<T>* temp = *p;
	*p = (*p)->m_nodes[(*p)->m_nodes[1]!=0];
	delete temp;
	return 1;
}

template <class T, class C>
void RedBlack<T,C>::inorder(CNode<T>* p){
	if (!p) return;
	inorder(p->m_nodes[0]);
	cout << p->m_x << " ";
	inorder(p->m_nodes[1]);
}

template <class T, class C>
void RedBlack<T,C>::printTree(CNode<T>* p){
	if (!p) return;
	cout << "Valor: " << p->m_x << " color: ";
	if (p->colour) cout << "Negro" << endl;
	else cout << "Rojo" << endl;
	if (p->m_nodes[0]) cout << "Hijo izquierdo: " << p->m_nodes[0]->m_x << ' ';
	if (p->m_nodes[1]) cout << "Hijo derecho: " << p->m_nodes[1]->m_x << endl;
	printTree(p->m_nodes[0]);
	printTree(p->m_nodes[1]);
}

template <class T>
void printTree(CNode<T>* head, int space) {
  if(head == NULL) {
    return;
  }
  space += 10;
  printTree(head->m_nodes[1], space);
  
  printf("\n");
  for(int i = 10; i < space; i++) {
     printf(" ");
  }
   printf("%d\n", head->m_x);
  printTree(head->m_nodes[0], space);
}



// int main(int argc, char *argv[]) {
// 	RedBlack<int, Menor<int> > RB;
// 	RB.insert(15); //RR test + RU
// 	RB.insert(18);
// 	RB.insert(21);
// 	RB.insert(14);
// 	RB.insert(5); //LL test + RU
// 	RB.insert(4);
// 	RB.insert(3);
// 	RB.insert(6);
// 	/*RB.insert(10); //LR test
// 	RB.insert(15);
// 	RB.insert(12);
// 	RB.insert(15); //RL test
// 	RB.insert(10);
// 	RB.insert(12);*/
// 	printTree(RB.m_root,4);
// 	return 0;
// }

