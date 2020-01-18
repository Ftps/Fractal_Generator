#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <complex>

#define XX 400.0

struct Pallete {
    int form, color_num;
    std::vector<std::string> colors;

    Pallete(const std::string& filename);
};

struct Img_Data : public Pallete {
    std::string name, filename;
    int it, res[2];
    bool Julia, preview;
    long double pp, zoom, k;
    std::complex<long double> cc, j_c;

    Img_Data(const std::string& filename) : Pallete(filename) {}
};

class Mandelbrot : private Img_Data {
    public:
        Mandelbrot(Img_Data&& img) : Img_Data(std::move(img)) {}
};
