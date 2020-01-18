#pragma once

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QSignalMapper>
#include <vector>

class Main_Menu : public QWidget {
    public:
        Main_Menu(QWidget *parent = 0);
        ~Main_Menu();
        int Next();
        void Reset();
    private:
        int next;
        QGridLayout *grid;
        std::vector<QPushButton*> btn;
        QSignalMapper *sigmap;
};
