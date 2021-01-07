#include <iostream>
#include <stack>
#include <queue>
#include <iomanip> // para emular identaciones 

template<class T>
class Node
{
public:
	Node(T );
	Node<T>* sons[2]; // Hijo derecho (0) e izquierdo (1)
	T data;

};
template<class T>
Node<T>::Node(T _data)
{
	sons[0] = sons[1] = 0;
	data = _data;
}

template<class T>
class BinaryTree
{
public:
	BinaryTree();
	bool find(T, Node<T>**&);
	bool insert(T);
	bool remove(T);
	Node<T>** placeRigth(Node<T>**);
	void print(Node<T>*, int identation = 0);
	void inOrder();
	void preOrder();
	void postOrder();
  void printLevel();
  void printOver(Node<T>*,int);

	Node<T>* root;
};

template<class T>
BinaryTree<T>::BinaryTree()
{
	root = nullptr;
}

template<class T>
bool BinaryTree<T>::find(T _data, Node<T>**& reference)
{
	for (reference = &root; 
		*reference && (*reference)->data != _data; 
		reference = &((*reference)->sons[(*reference)->data < _data]))
	{ }
	return !!*reference;
}

template<class T>
bool BinaryTree<T>::insert(T _data)
{
	Node<T>** reference;
	if (find(_data, reference))
		return 0;
	*reference = new Node<T>(_data);
	return 1;
}

template<class T>
Node<T>** BinaryTree<T>::placeRigth(Node<T>** reference)
{
	Node<T>** aux;
	for (aux = &(*reference)->sons[0]; (*aux)->sons[1] != 0; aux = &(*aux)->sons[1])
	{	}
	return aux;
}

template<class T>
bool BinaryTree<T>::remove(T _data)
{
	Node<T>** reference;
	if (!find(_data, reference))
		return 0;
	if ((*reference)->sons[0] && (*reference)->sons[1])
	{
		Node<T>** aux;
		aux = placeRigth(reference);
		(*reference)->data = (*aux)->data;
		reference = aux;
	};
	Node<T>* temp = *reference;
	*reference = (*reference)->sons[!!(*reference)->sons[0]];
	delete temp;
	return 1;
}

template<class T>
void BinaryTree<T>::print(Node<T>* reference, int identation)
{
	if (!reference)
		return;
	print(reference->sons[1], identation + 4);
	if (identation)
		std::cout << std::setw(identation) << ' ';
	std::cout << "" << reference->data << std::endl;
	print(reference->sons[0], identation + 4);
	return;
}

template<class T>
void BinaryTree<T>::inOrder()
{
	std::stack<Node<T>*> pila;
	Node<T>* current = this->root;
	while (current || !pila.empty() )
	{
		while (current)
		{
			pila.push(current);
			current = current->sons[0];
		}
		current = pila.top();
		pila.pop();
		std::cout << current->data << " ";
		current = current->sons[1];
	}
	std::cout << std::endl;
}

template<class T>
void BinaryTree<T>::preOrder()
{
	std::stack<Node<T>*> pila;
	Node<T>* current = this->root;
	while (current || !pila.empty())
	{
		while (current)
		{
			std::cout << current->data << " ";
			pila.push(current);
			current = current->sons[0];
		}
		current = pila.top();
		pila.pop();		
		current = current->sons[1];
	}
	std::cout << std::endl;
}

template<class T>
void BinaryTree<T>::postOrder()
{
	std::stack<Node<T>*> pila1;
	std::stack<Node<T>*> pila2;

	Node<T>* current;
	pila1.push(this->root);


	while (!pila1.empty())
	{
		current = pila1.top();
		pila1.pop();
		pila2.push(current);
		if (current->sons[0])
			pila1.push(current->sons[0]);
		if (current->sons[1])
			pila1.push(current->sons[1]);
		while (!pila2.empty())
		{
			current = pila2.top();
			pila2.pop();
			std::cout << pila1.top()->data <<" ";			
		}			
	}
}


template<class T>
void BinaryTree<T>::printLevel()
{
  if (!this->root)
    return;
  std::queue<Node<T>*> cola;
  cola.push(this->root);

  while (!cola.empty())
  {
    int nodeCount = cola.size();
    while (nodeCount > 0)
    {
      Node<T>* aux = cola.front();
      std::cout << aux->data << " ";
      cola.pop();
      if (aux->sons[0])
        cola.push(aux->sons[0]);
      if (aux->sons[1])
        cola.push(aux->sons[1]);
      nodeCount--;
    }
    //std::cout << std::endl;
  }  
}

template<class T>
void BinaryTree<T>::printOver(Node<T>* head, int spaces)
{
  if(head == NULL) {
    return;
  }
  spaces += 10;
  printOver(head->sons[1], spaces);
  
  printf("\n");
  for(int i = 10; i < spaces; i++) {
     printf(" ");
  }
   printf("%d\n", head->data);
  printOver(head->sons[0], spaces);
}

/* MAIN SETUP PANEL */
/*
int main()
{
	BinaryTree<int> test;

	int option, n;
	while (true) {
		std::cout << " |*************** Arbol Binario ***************| " << std::endl;
		std::cout << " |* Presiona (1) Para Insertar un nodo        *| " << std::endl;
		std::cout << " |* Presiona (2) Para Eliminar un nodo        *| " << std::endl;
		std::cout << " |* Presiona (3) Para Recorrido en Pre-Orden  *| " << std::endl;
		std::cout << " |* Presiona (4) Para Recorrido en In-Orden   *| " << std::endl;
		std::cout << " |* Presiona (5) Para Recorrido en Post-Orden *| " << std::endl;
    std::cout << " |* Presiona (6) Para Imprimir por niveles    *| " << std::endl;
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
				test.print(test.root);
			}
		}
		else if (option == 2) {
			std::cout << "\n\n Presiona (0) para volver al menu anterior, borrar el numero: " << std::endl;
			std::cin >> n;
			test.remove(n);
			test.print(test.root);
		}
		else if (option == 3) {
			std::cout << "\n\n El recorrido en Pre-Orden es: " << std::endl;
			test.preOrder();
		}
		else if (option == 4) {
			std::cout << "\n\n El recorrido en In-Orden es: " << std::endl;			
			test.inOrder();
		}
		else if (option == 5) {
			std::cout << "\n\n El recorrido en Post-Orden es: " << std::endl;
			test.postOrder();
		}
    else if (option == 6) {
			std::cout << "\n\n Impresion por Niveles: " << std::endl;
      test.printLevel();
      std::cout << std::endl;
		}
		else if (option == 0)
			break;
	}

	return 0;
}
*/