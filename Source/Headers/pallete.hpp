#pragma once

#include "gui_extra.hpp"
#include "mandel_qt.hpp"

class Pallete_GUI : public QWidget {
    public:
        Pallete_GUI(QWidget *parent = 0);
        ~Pallete_GUI();
    private:
        QGridLayout *grid;
        std::vector<QLabel*> labels;
        std::vector<QPushButton*> btns;
        std::vector<QLineEdit*> lines;

        void CreatePallete();
        void AddColor();
        void Interpolate();
        void Delete();
};
