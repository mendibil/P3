#include <vector>
#include <iostream>
using namespace std;

int main() {
  //declara un vector de int, sin tamaño
  vector<int> x;
  if (x.empty())
    cout << "x is an empty vector\n";


  //cambia tamaño a 10
  x.resize(10);

  //se accede como vectores en C
  for (int i=0; i < x.size(); i++) x[i] = i*10;
  for (int i=0; i < x.size(); i++) cout << x[i] << ' ';
  cout << '\n';
  
  
  //se añaden valores al fina: el vector tendrá tamaño 12
  x.push_back(100);
  x.push_back(110);
  cout << "Size: " << x.size() << '\n';
  cout << "Last value: " << x.back() << '\n';

  //se copia un vector en otro
  vector<int> y = x;
  
  //borrar un vector; queda sin tamaño
  x.clear();
  if (x.empty())
    cout << "x is an empty vector\n";
  if (!y.empty())
    cout << "Size of y: " << y.size() << '\n';

  //En vectores C, se pueden usar punteros,
  float xc[10];
  float *p;
  for (p = xc; p != xc + 10; p++)
    *p = 0;

  //En c++, la generalización, iteradores, que pueden usarse para otros contenedores
  vector<int>::iterator it;
  for (it = y.begin(); it != y.end(); it++) {
    *it /= 10; 
    cout << *it << ' ';
  }
  cout << '\n';

   
  return 0;
}


#if 0
Resultados:

x is an empty vector
0 10 20 30 40 50 60 70 80 90 
Size: 12
Last value: 110
x is an empty vector
Size of y: 12
#endif
