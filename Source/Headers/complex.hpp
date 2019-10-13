#ifndef COMPLEX
#define COMPLEX

#include <cmath>
#include <iostream>

#define PI 3.14159

class Complex {
    long double x, y;
public:
    Complex(long double, long double);
    void add(Complex);
    void sub(Complex);
    void mul(Complex);
    void div(Complex);
    void scalar(long double);
    void power(int);
    long double modu();
    long double modu2();
    long double arg();
    void conj();
};

#endif
