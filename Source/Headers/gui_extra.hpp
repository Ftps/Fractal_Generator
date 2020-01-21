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
#include <QStringList>
#include <QProgressBar>
#include <vector>
#include <filesystem>

// for debug
#include <iostream>
#include <QTextStream>
#include <typeinfo>

#define W_X 100
#define W_Y 50

class Error_Qt : public QWidget {
    public:
        Error_Qt(const QString& err_msg, QWidget *parent = 0);
        ~Error_Qt();
    private:
        QGridLayout *grid;
        QPushButton *btn;
        std::vector<QLabel*> msg;

        void Okay();
};


bool isIntegerP(const std::string& s);
bool isLDouble(const std::string& s);

template<typename T>
QLabel* new_label(T* tt, const QString& name = "", int length = 1, int heigth = 1)
{
    QLabel *emp = new QLabel(name, tt);
    emp->setFixedSize(W_X*length, W_Y*heigth);
    emp->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    emp->setWordWrap(true);

    return emp;
}

template<typename T>
QLineEdit* new_line(T* tt, int size = 2)
{
    QLineEdit *emp = new QLineEdit(tt);
    emp->setFixedSize(W_X*size, W_Y);

    return emp;
}

QPushButton* new_btn(const QString& name, int size = 2);
