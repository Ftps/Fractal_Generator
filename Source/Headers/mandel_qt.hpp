#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <complex>

#include <QColor>
#include <QImage>
#include <QPainter>

#define LOG {std::cout << "IN FILE " << __FILE__ << " IN LINE " << __LINE__ << std::endl; }

#define XX 400.0
#define LL 4

#define PAL_PATH "Config/Pallete/"
#define PAL_EXT ".pl"
#define IMG_EXT ".png"
#define IMG_PATH "Images/"

struct Pallete {
    int form, color_num;
    std::vector<QColor*> colors;

    Pallete(const std::string& filename);
};

struct Img_Data : public Pallete {
    std::string name, filename;
    int it;
    std::array<int, 2> res;
    bool Julia, preview;
    long double pp, zoom, k;
    std::complex<long double> cc, cj;

    Img_Data(const std::string& filename) : Pallete(filename) { this->filename = filename; }
};

class Mandelbrot : private Img_Data {
    public:
        Mandelbrot(const Img_Data& img);
        QImage get_image();
    private:
        std::vector<std::vector<int>> map;
        QImage *image;

        void generate_p2();
        void generate_p3();
        void generate_pn();
        void draw_image();
};

template<typename T>
T abs2(std::complex<T> c);

inline long double abs1(long double a, long double b);
