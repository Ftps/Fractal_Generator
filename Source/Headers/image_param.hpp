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
#include <string>
#include <vector>
#include <unistd.h>

// for debug
#include <iostream>
#include <QTextStream>
#include <typeinfo>

#define W_X 100
#define W_Y 50
#define GetCurrentDir getcwd

struct Image_Data{
    std::string name, pal;
};

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

        QLabel* new_label(QString name = "", int length = 1, int heigth = 1);
        QLineEdit* new_line(int size = 2);
        QPushButton* new_btn(QString name);
        void UpdatePreview();
        void Run();
};

std::string GetCurrentWorkingDir(void);
