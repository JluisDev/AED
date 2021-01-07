#include <iostream>
#include <list>
#include <vector>

template <class G>
struct CNode{
  typedef typename G::Edge Edge;
  typedef typename G::n N;
  N m_data;
  std::list<Edge*> m_edges; //TIL: STL list = Double Linked List
};


template <class G>
struct CEdge{
  typedef typename G::Node Node;
  typedef typename G::e E;
  Node* m_nodes[2];
  E m_data;
  bool m_dir; //0, <->; 1, m_nodes[0]->m_nodes[1]
};

template <class N, class E>
class CGraph {
    public:
      typedef CGraph <N,E> self;
      typedef CNode<self> Node;
      typedef CEdge<self> Edge;
      typedef N n;  // N es privado con esta declaracion la volvemos publica y accesible para otras clases
      typedef E e;  // E es privado con esta declaracion la volvemos publica y accesible para otras clases

      std::vector<Node*> m_nodes;

      void insertNode(N );
      void insertEdge(E, Node*, Node*, bool);  // Insertamos la arista, nodo de inicio, nodo destinatario, la direccion
      void removeEdge(E, Node*, Node*);
      void removeNode(Node* );

      void print();
};


template<class N, class E>
void CGraph<N, E>::insertNode(N node) {
  Node* temp = new Node;
  temp->m_data = node;
  m_nodes.push_back(temp);   
}

template<class N, class E>
void CGraph<N, E>::insertEdge(E edge, Node* a, Node* b, bool dir) {
  Edge* temp = new Edge;
  temp->m_data = edge;
  temp->m_nodes[0] = a;  // predecesor: del nodo que se parte
  temp->m_nodes[1] = b;  // Al nodo que se llega
  temp->m_dir = dir;
  a->m_edges.push_back(temp);
  b->m_edges.push_back(temp);
}

template<class N, class E>
void CGraph<N,E>::removeEdge(E edge, Node* a, Node* b) {
  typename std::list<Edge*>::iterator it;
  for (it = a->m_edges.begin(); it != a->m_edges.end() ; it++){
    if ((*it)->m_data == edge){
      if (( (*it)->m_nodes[0] == a && (*it)->m_nodes[1] == b ) || ((*it)->m_nodes[0] == b && (*it)->m_nodes[1] == a ))
        break;
    }
  }
  
  a->m_edges.erase(it);
  
  for (it = b->m_edges.begin(); it != b->m_edges.end() ;it++)
  {
    if ((*it)->m_data == edge) {
      if (((*it)->m_node[0] == a && (*it)->m_node[1] == b ) || ((*it)->m_node[0] == b && (*it)->m_node[1] == a ))
        break;
    }
  }

  b->m_edges.erase(it);

  delete *it;  
}

template<class N, class E>
void CGraph<N,E>::removeNode(Node* a){
  typename std::list<Edge*>::iterator temp;
  typename std::list<Edge*>::iterator it = a->m_edges.begin();

  while(it != a->m_edges.end) {
    temp = it++;
    removeEdge((*temp)->m_data, (*temp)->m_node[0], (*temp)->m_node[1]);
  }
  delete a;

  typename std::vector<Node*>::iterator itr = std::find(m_nodes.begin(), m_nodes.end(), a);

  m_nodes.erase(m_nodes.begin() + std::distance(m_nodes.begin(), itr));
}

template <class N, class E>
void CGraph<N, E>::print(){
	for(uint i = 0; i < m_nodes.size(); i++){
		std::cout << m_nodes[i]->m_data << "->";
		for(typename std::list<Edge*>::iterator it = m_nodes[i]->m_edges.begin(); it != m_nodes[i]->m_edges.end(); ++it){
			if ((*it)->m_nodes[0] == m_nodes[i]) std::cout << (*it)->m_data << (*it)->m_nodes[1]->m_data << " -> "; //cuando la arista tiene direccion 1
			else if (!(*it)->m_dir) std::cout << (*it)->m_data << (*it)->m_nodes[0]->m_data<< " <-> "; //cuando la arista es bidireccional
		} //mejorar esta parte si se puede
		std::cout << std::endl;
	}
}