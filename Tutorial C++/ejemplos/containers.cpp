#include <iostream>
#include <list>
#include <map>
using namespace std;

int main() {
  // **** LISTA ***

  //declara una list
  list<int> x;
  if (x.empty())
    cout << "x is an empty list\n";

  //añadir 20 elementos
  for (int i=0; i<10; i++) {
    x.push_back(i);
    x.push_back(0);
  }

  //no está implementado x[i] para evitar tentaciones:
  //en una lista ésta es una operación costosa, pues hay que ir de elemento en elemento.
  
  // Usaremos iteradores para acceder elementos
  // const_iterator indica que no modificaremos; no sería posible *it = 4;
  list<int>::const_iterator itc;
  for (itc = x.begin(); itc != x.end(); itc++) cout << *itc << ' ';
  cout << '\n';

  //Borrar elementos con valor cero:
  list<int>::iterator it;
  for (it = x.begin(); it != x.end();) {
    if (*it == 0) it = x.erase(it);
    else ++it;
  }  
  for (itc = x.begin(); itc != x.end(); itc++) cout << *itc << ' ';
  cout << '\n';
  
  // **** MAPA, the int_ID to float ***

  map<int, float> m;

  m[100000] = 2.7183;
  m[401962] = 1.4142;
  m[0]      = 3.1416;

  map<int,float>::iterator m_it;

  cout << "Map size: " << m.size() << '\n';
  for (m_it = m.begin(); m_it != m.end(); ++m_it) {
    cout << m_it->first << " => " << m_it->second << '\n';
  }

  int keys[4] = {7, 100000, 13, 0};
  for (int i=0; i<4; i++) {
    m_it = m.find(keys[i]);
    if (m_it != m.end())
      cout << keys[i] << " => " << m_it->second << '\n';
    else
      cout << keys[i] << " not found\n";
  }
  
  return 0;
}


#if 0
Resultados:

x is an empty list
0 0 1 0 2 0 3 0 4 0 5 0 6 0 7 0 8 0 9 0 
1 2 3 4 5 6 7 8 9 
Map size: 3
0 => 3.1416
100000 => 2.7183
401962 => 1.4142

7 not found
100000 => 2.7183
13 not found
0 => 3.1416
	      
#endif
