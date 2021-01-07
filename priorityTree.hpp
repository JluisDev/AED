#include <iostream>
#include <cmath>

template<class T>
class Node {
 public:
  Node(T );
  Node<T>* sons[3]; // 0 Izquierdo 1 Derecho 2 padre
  T data;
};

template<class T>
Node<T>::Node(T _data) {
  data = _data;
  sons[0] = sons[1] = nullptr;
}



template<class T>
void treeBuild(Node<T>* &root, Node<T>* nodeArray[100], int counter); 

template<class T>
void Heapify(Node<T>* node1, Node<T>* node2, Node<T>* root);

template<class T>
void printTree(Node<T>* root, int space);

template<class T>
void treeBuild(Node<T>* &root, Node<T>* nodeArray[200], int counter) {
  for(int i = 1; i < counter + 1; i++) {
    //establecemos el indice en la raiz del arbol
    if(i == 1) {
      root = nodeArray[i];
    }
    else {
      //Cantidad de nodos y los dividimos entre 2 
      int parent = -1;
      parent = trunc(i / 2);
      //Si el padre no tiene hijo izquierdo balanceamos 
      if(nodeArray[parent]->sons[0] == NULL) {;
				nodeArray[parent]->sons[0] = nodeArray[i];
				nodeArray[i]->sons[2] = nodeArray[parent];
				Heapify(nodeArray[parent], nodeArray[i], root);
			}
      //Si el papa tiene hijo izquierdo insertamos en el hijo derecho y balanceamos
      else {
				nodeArray[parent]->sons[1] = nodeArray[i];
				nodeArray[i]->sons[2] = nodeArray[parent];
				Heapify(nodeArray[parent], nodeArray[i], root);
      }
    }
  }
}

template<class T>
void Heapify(Node<T>* node1, Node<T>* node2, Node<T>* root) {
  //Si el primer nodo es mas grande que el primero swapeamos
  if(node2->data > node1->data) {
    T temp = node2->data;
    node2->data = node1->data;
    node1->data = temp;
    //si no es la raiz recursividad forever :v 
    if(node1->data != root->data) {
      Heapify(node1->sons[2], node2->sons[2], root);
    }
  }
}

template<class T>
void printTree(Node<T>* root, int space) {
  if(root == NULL) {
    return;
  }
  space += 10;
  printTree(root->sons[1], space);
  
  std::cout<<std::endl;
  for(int i = 10; i < space; i++) {
    std::cout<<" ";
  }
  
  std::cout<< root->data<<std::endl;
  printTree(root->sons[0], space);
}

/* MAIN SETUP PANEL */

/*
int main() {
  Node<int>* nodeArray[100];  

	std::vector<int> datos;
	Node<int>* head;

	int option, n, counter;
	while (true) {
		std::cout << " |*********** Arbol de Prioridades ************| " << std::endl;
		std::cout << " |* Presiona (1) Para Insertar un nodo        *| " << std::endl;
		std::cout << " |* Presiona (2) Para Imprimir el arbol       *| " << std::endl;
		std::cout << " |* Presiona (3) Para Eliminar Numeros        *| " << std::endl;
		std::cout << " |* Presiona (0) Para Salir del Programa      *| " << std::endl;
		std::cout << " |*********************************************| " << std::endl;
		std::cin >> option;
		if (option == 1) {
			while (true) {
				std::cout << "\n\n Presiona (0) para volver al menu anerior, ingrese un numero: " << std::endl;
				std::cin >> n;
				datos.push_back(n);
				if (n == 0)
					break;
			}
			datos.erase(datos.end()-1); // BORRAMOS EL 0 DEL MENU :V

			counter = datos.size();
			

			for(int i = 0; i < counter; i++) {
				Node<int>* newNode = new Node<int>(datos[i]);
				nodeArray[i + 1] = newNode;
			}
			treeBuild(head, nodeArray, counter);
		}
		else if (option == 2){

			nodeArray[0] = NULL;

			// for (int i = 0; i < datos.size(); i++)
			// {
			// 	std::cout<< datos[i]<< " - ";
			// }			

			//std::cout << "" << std::endl;

			printTree(head, 0);

			std::cout << "" << std::endl;

		}
		else if (option == 3){

			int newsize = datos.size();		

			int deleteNumbers;

			std::cout << "\n\n Ingrese la cantidad de numeros a eliminar: " << std::endl;
			std::cin >> deleteNumbers;

			std::vector<int> datos2;

			Node<int>* headDelete;
			Node<int>* nodeArrayDelete[100]; 


			for (int i = 0; i < newsize; i++)
			{
				datos2.push_back(nodeArray[i+1]->data);
			}
	

			sort(datos2.begin(), datos2.end(), std::greater<int>());

			datos2.resize(datos2.size()-deleteNumbers);

			// for (auto x : datos2) 
			// 		std::cout << x << " "; 

			
			for(int i = 0; i < datos2.size(); i++) {
				Node<int>* newNodeDelete = new Node<int>(datos2[i]);
				nodeArrayDelete[i + 1] = newNodeDelete;
			}
			treeBuild(headDelete, nodeArrayDelete, datos2.size());

			nodeArrayDelete[0] = NULL;


			printTree(headDelete, 0);

			std::cout << "" << std::endl;
		}

		

		else if (option == 0)
			break;
	}

  return 0;
}
*/