#ifndef MANDEL_CPP
#define MANDEL_CPP

#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <boost/format.hpp>

#define PY_SSIZE_T_CLEAN
#include "Py/Python.h"
#include "complex.hpp"

#define GUI "Source/Files/GUI/"
#define PALLETE "Config/Pallete/"
#define TEMP "Config/Temp/temp.mdb"
#define IMAGE "Images/"
#define XPM_HEAD "/* XPM */\nstatic char * img_xpm[] = {\n"

#define LOG {std::cout << "IN LINE " << __LINE__ << " IN FILE " << __FILE__ << "\n"; fflush(stdout);}
#define vec(X) std::vector<X>
#define mat(X) vec(vec(X))
#define S (std::string)
#define SS(X) std::to_string(X)

#define PI 3.14159

struct Pallete {
    int color_num, r;
    vec(std::string) color;

    Pallete(std::string);
    void print_pallete(std::ofstream&, boost::format);
};

struct Img_Data {
    int x, y;
    std::string name;

    Img_Data(int, int, std::string);
};

class Image {
    Pallete* c;
    Img_Data* img;
    std::string head_xpm;
    long double cc[2], j_c[2];
    long double l, h, z, con, pp;
    int it;
    bool julia;
    mat(int) map;
    long double modu(long double, long double);

public:
    Image(std::string);
    ~Image();
    void generate_p2();
    void generate_p3();
    void generate_pn();
    void generate_image();
    long double power();
    void print_param();
};


void generate_pallete();
void mandelbrot();

#endif
