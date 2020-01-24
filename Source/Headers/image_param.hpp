#pragma once

#include <thread>

#include "mandel_qt.hpp"
#include "gui_extra.hpp"

class Image_Param : public QWidget {
    public:
        Image_Param(QWidget *parent = 0);
        ~Image_Param();
    private:
        Img_Data *data;
        QGridLayout *grid;
        QLabel *prev, *current;
        QProgressBar *prog;
        Error_Qt *error;
        bool terminated;
        std::vector<QLabel*> labels;
        std::vector<QLineEdit*> lines;
        std::vector<QComboBox*> combos;
        std::vector<QPushButton*> btns;
        std::thread *m;

        int InspectValues();
        void Preview();
        void Run();
        QStringList GetPallete();
        void GetImg_Data(bool preview);
        void getProg(int value);
        void getCurr(QString doing);
        void Connect(Mandelbrot *mandel);
};
