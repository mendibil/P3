#include <string>
#include <iostream>
using namespace std;
int main() {

  //hello world
  string h = "hello";
  string w = "world";

  string s = h + ' ' + w;
  cout << s << '\n';
  if(! s.empty()) {
    cout << s.size() << "\n\n";
  }

  //Read words and delete vowels
  int num_words = 0;
  while (cin >> s) {
    string::size_type pos = s.find_first_of("aeiou");
    while (pos != string::npos)  {
      s[pos]='.';
      pos=s.find_first_of("aeiou",pos+1);
    }    
    cout << ++num_words << '\t' << s << endl;
  }
}

#if 0
Results:
echo "no por mucho madrugar amanece más temprano" | ./string
hello world
11

1	n.
2	p.r
3	m.ch.
4	m.dr.g.r
5	.m.n.c.
6	más
7	t.mpr.n.
#endif
