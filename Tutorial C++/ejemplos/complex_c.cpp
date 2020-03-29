#include <iostream>
#include <math.h>
using namespace std;

struct Complex {
  float r, i;
};

void complex_set(Complex *c, float re, float im) {
  c->r = re;
  c->i = im;
}

float complex_abs(const Complex *c) {
  return sqrt(c->r * c->r + c->i * c->i);
}

void complex_add(Complex *c, const Complex *c1, const Complex *c2) {
  c->r = c1->r + c2->r;
  c->i = c1->i + c2->i;
}


int main() {
  Complex v1, v2, *ptv2 = &v2;
  complex_set(&v1, 1, -1);  //v1.r = 1; v1.i = -1;
  complex_set(ptv2, 2,  1); //ptv2->r = 2 or v2.r = 2, etc.
  cout << complex_abs(&v1) << ' ' << complex_abs(ptv2) << '\n';
}




