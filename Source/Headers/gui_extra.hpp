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
#include <QStringList>

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
