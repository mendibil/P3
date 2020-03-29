#include <iostream>
#include <math.h>
using namespace std;

class Complex {
private:
  float r, i;
public:
  void set(float re, float im) {r = re; i = im;}
  float abs() {return sqrt(r * r + i * i);}
  bool operator==(const Complex &c) const {
    if (c.r == r and c.i == i) return true;
    else return false;
  }
  const Complex & operator=(const Complex &c) {
    r = c.r;
    i = c.i;
    return *this;
  }
};

int main() {
  Complex c1, v[2], *ptc = v+1;
  c1.set(0,1);
  v[0].set(3,  -4);
  v[1].set(1, -1);
  cout << c1.abs() << ' ' << v[0].abs() << ' ' << ptc->abs() << '\n';

  v[1] = c1;
  if (v[1] == c1) cout << "Equal values!\n";
  else cout << "Different values\n";  
}

