#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <complex>

#define LOG {std::cout << "IN FILE " << __FILE__ << " IN LINE " << __LINE__ << std::endl; }

#define XX 400.0
#define LL 4

#define PAL_PATH "Config/Pallete/"
#define PAL_EXT ".pl"
#define IMG_EXT ".png"

struct Pallete {
    int form, color_num;
    std::vector<std::string> colors;

    Pallete(const std::string& filename);
};

struct Img_Data : public Pallete {
    std::string name, filename;
    int it;
    std::array<int, 2> res;
    bool Julia;
    long double pp, zoom, k;
    std::complex<long double> cc, cj;

    Img_Data(const std::string& filename) : Pallete(filename) { this->filename = filename; }
};

class Mandelbrot : private Img_Data {
    public:
        Mandelbrot(const Img_Data& img);
        void run();
    private:
        std::vector<std::vector<int>> map;

        void generate_p2();
        void generate_p3();
        void generate_pn();
};

template<typename T>
T abs2(std::complex<T> c);
