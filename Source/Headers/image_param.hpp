#pragma once

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QSignalMapper>
#include <QLineEdit>
#include <QComboBox>
#include <QPixmap>
#include <vector>

#include "mandel_qt.hpp"

// for debug
#include <iostream>
#include <QTextStream>
#include <typeinfo>

#define W_X 100
#define W_Y 50

class Image_Param : public QWidget {
    public:
        Image_Param(QWidget *parent = 0);
        ~Image_Param();
    private:
        QGridLayout *grid;
        QLabel *prev;
        std::vector<QLabel*> labels;
        std::vector<QLineEdit*> lines;
        std::vector<QComboBox*> combos;
        std::vector<QPushButton*> btns;

        QLabel* new_label(const QString& name = "", int length = 1, int heigth = 1);
        QLineEdit* new_line(int size = 2);
        QPushButton* new_btn(const QString& name);
        int InspectValues();
        void UpdatePreview();
        void Run();
};

inline bool isInteger(const std::string& s);
