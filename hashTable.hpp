#include <iostream>
#include <set>
#include <vector>
#include <iterator>

/* ADAPTADOR DEL ARBOL */

template<class TA>
class setAdapter {
  public:
  std::set<TA> my_tree;
  bool insert(TA );
  bool find(TA );
  bool remove(TA );
  void printdata();
};

template<class TA>
bool setAdapter<TA>::insert(TA _data){
  my_tree.insert(_data);
}

template<class TA>
void setAdapter<TA>::printdata(){
  typename std::set<TA>::iterator it;
  for (it=my_tree.begin(); it!=my_tree.end(); ++it)
    std::cout << ' ' << *it << ' ';
  std::cout << std::endl;
}


template<class TA>
bool setAdapter<TA>::find(TA _data) {
  typename std::set<TA>::iterator it;
  for (it = my_tree.begin(); it != my_tree.end(); it++){
    if (*it == _data)
      return 1;
  }
  return 0;  
}

template<class TA>
bool setAdapter<TA>::remove(TA _data) {
  typename std::set<TA>::iterator it;
  for ( it = my_tree.begin(); it != my_tree.end(); it++){
    if (*it == _data){
      my_tree.erase(it);
      return 1;
    }
  }
  return 0;
}

template <class T, class E, class F, long Z>  // T => tipo de dato, E => Estructura que almacena las colisiones, F => functor (funcion de dispersion), Z => el tamanho sobre el universo que se trabaja
class HashTable {
  public:
    F dispersion;
    std::vector<E> path;
    HashTable();
    bool insert(T );
    bool find(T );
    bool remove(T );
    void print();
};

template <class T, class E, class F, long Z>
HashTable<T,E,F,Z>::HashTable() {
  path.resize(Z);
}

template <class T, class E, class F, long Z>
bool HashTable<T,E,F,Z>::insert(T _data){
  return path[dispersion(_data)].insert(_data);
}

template <class T, class E, class F, long Z>
bool HashTable<T,E,F,Z>::find(T _data){
  return path[dispersion(_data)].find(_data);
}

template <class T, class E, class F, long Z>
bool HashTable<T,E,F,Z>::remove(T _data){
  return path[dispersion(_data)].remove(_data);
}

template <class T, class E, class F, long Z>
void HashTable<T,E,F,Z>::print(){
  for (int i = 0; i < path.size(); i++)
  {    
    path[i].printdata();
  }
}


/* SETUP MAIN PANEL */

/*

#include <iostream>
#include "hashTable.hpp"
*/

/* DECLARAMOS EL FUNCTOR PARA HACER LA FUNCION DE DISPERSION */
/*
template<class T>
struct functionHash{
  inline T operator()(T a){
    return a%5;
  }
};


int main() {

  HashTable<int,setAdapter<int>, functionHash<int>, 4> ht;

  ht.insert(10);
  ht.insert(15);
  ht.insert(13);
  ht.insert(20);
  ht.insert(17);
  ht.insert(21);
  ht.insert(12);
  ht.insert(11); 

  ht.remove(11);

  ht.print();

  return 0;
}
*/