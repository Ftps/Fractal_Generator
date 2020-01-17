#ifndef GUI_HPP
#define GUI_HPP

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QGridLayout>
#include <QVBoxLayout>
#include <vector>

// for debug
#include <iostream>
#include <QTextStream>
#include <typeinfo>

class Main_Menu : public QWidget { Q_OBJECT
    public:
        Main_Menu(QWidget* parent = 0);
        int Next();
    private:
        int next;

        void Action(QString name);
        void Gen_Pic();
        void Gen_Pal();
        void Quit();
};

#endif
