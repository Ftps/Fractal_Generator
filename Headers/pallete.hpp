#pragma once

#include "gui_extra.hpp"
#include "mandel_qt.hpp"

#define ALPHA_CHAN 4278190080

class Pallete_GUI : public QWidget {
    public:
        Pallete_GUI(QWidget *parent = 0);
        ~Pallete_GUI();
    private:
		QTableWidget *table;
        bool clear;
        QGridLayout *grid;
        QHeaderView *header;
		QLabel *prev;
        std::vector<QLabel*> labels;
        std::vector<QPushButton*> btns;
        std::vector<QLineEdit*> lines;
        std::vector<QColor*> colors;
        std::vector<int> iters;

        void CreatePallete();
        void AddColor();
        void Interpolate();
        void Delete();
        void WriteFile();
};


inline std::array<int, 3> operator-(const std::array<int, 3>& one, const std::array<int, 3>& two)
{
    std::array<int, 3> nee;

    for(int i = 0; i < 3; ++i){
        nee[i] = one[i] - two[i];
    }

    return nee;
}

template<typename T>
inline std::array<double, 3> operator/(const std::array<int, 3>& vec, const T& scalar)
{
    std::array<double, 3> nee;

    for(int i = 0; i < 3; ++i){
        nee[i] = vec[i]/scalar;
    }

    return nee;
}

inline std::array<int, 3> operator+(const std::array<int, 3>&one, const std::array<double, 3>& two)
{
    std::array<int, 3> nee;

    for(int i = 0; i < 3; ++i){
        nee[i] = one[i] + (int)two[i];
    }

    return nee;
}

inline std::array<double, 3> operator*(const int scalar, const std::array<double, 3>& vec)
{
    std::array<double, 3> nee;

    for(int i = 0; i < 3; ++i){
        nee[i] = ((double)scalar)*vec[i];
    }

    return nee;
}

QRgb get_rgb(const std::array<int, 3> color);
