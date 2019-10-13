#include "../Headers/complex.hpp"

Complex::Complex(long double re, long double im){
    x = re;
    y = im;
}

void Complex::add(Complex C)
{
    x += C.x;
    y += C.y;
}

void Complex::sub(Complex C)
{
    x -= C.x;
    y -= C.y;
}

void Complex::mul(Complex C)
{
    long double aux;

    aux = x*C.x - y*C.y;
    y = x*C.y + y*C.x;
    x = aux;
}

void Complex::div(Complex C)
{
    C.conj();
    mul(C);
    scalar(1/C.modu2());
}

void Complex::scalar(long double k)
{
    x = k*x;
    y = k*y;
}

void Complex::power(int p)
{
    Complex C(x, y);

    for(int i = 0; i < p; ++i){
        mul(C);
    }
}

long double Complex::modu()
{
    return sqrt(x*x + y*y);
}

long double Complex::modu2(){
    return x*x + y*y;
}

long double Complex::arg(){
    if(x == 0){
        if(y > 0){
            return PI/2;
        }
        else if(y < 0){
            return 3*PI/2;
        }
        else return 0;
    }
    else{
        return atan(y/x);
    }
}

void Complex::conj()
{
    y = -y;
}
