#include <map>
#include <string>
#include <iostream>
using namespace std;


int main() {
  map<string, int> dict;
  string s;
  //Leer de palabra en palabra, desde entrada estándar
  //y crear diccionario

  int id = 0;
  while (cin >> s) {
    if (dict.find(s) == dict.end())
      dict[s] = ++id;
  }

  //Mostrar diccionario
  map<string,int>::iterator idict;
  for (idict = dict.begin(); idict != dict.end(); ++idict)
    cout << idict->first << ": " << idict->second << '\n';
  cout << "------------------------\n";
    
  //Buscar palabra en diccionario
  s = "isabel";
  idict = dict.find(s);
  if (idict == dict.end())
    cout << s << " not found in dict\n";
  else
    cout << s << ": " << dict[s] << '\n';
}

#if 0
Results:

$ echo tanto monta monta tanto isabel como fernando | ./string_map 
como: 4
fernando: 5
isabel: 3
monta: 2
tanto: 1
------------------------
isabel: 3
#endif
