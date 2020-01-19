#pragma once

#include <filesystem>

#include "mandel_qt.hpp"
#include "gui_extra.hpp"

class Image_Param : public QWidget {
    public:
        Image_Param(QWidget *parent = 0);
        ~Image_Param();
    private:
        Img_Data *data;
        QGridLayout *grid;
        QLabel *prev;
        std::vector<QLabel*> labels;
        std::vector<QLineEdit*> lines;
        std::vector<QComboBox*> combos;
        std::vector<QPushButton*> btns;

        int InspectValues();
        void Preview();
        void Run();
        QStringList GetPallete();
        void GetImg_Data(bool preview);
};

template<typename T>
QLabel* new_label(T* tt, const QString& name = "", int length = 1, int heigth = 1);

template<typename T>
QLineEdit* new_line(T* tt, int size = 2);

QPushButton* new_btn(const QString& name);
