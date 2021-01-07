#include <iostream>

//#include "priorityTree.hpp"
//#include "avlTree.hpp"
//#include "redblackTree.hpp"

#include "graph.hpp"
//#include "hashTable.hpp"


int main() {

  CGraph<char, int> g;

  g.insertNode('A');  // 0
  g.insertNode('B');  // 1
  g.insertNode('D');  // 2
  g.insertNode('D');  // 3
  g.insertNode('E');  // 4

  g.insertEdge(14, g.m_nodes[0], g.m_nodes[4], 0);
	g.insertEdge(7, g.m_nodes[0], g.m_nodes[1], 0);
	g.insertEdge(9, g.m_nodes[1], g.m_nodes[2], 0);
	g.insertEdge(10, g.m_nodes[1], g.m_nodes[2], 0);
	g.insertEdge(15, g.m_nodes[1], g.m_nodes[3], 0);
	g.insertEdge(11, g.m_nodes[2], g.m_nodes[3], 0);
	g.insertEdge(2, g.m_nodes[2], g.m_nodes[4], 0);

  g.print();

  return 0;
}
