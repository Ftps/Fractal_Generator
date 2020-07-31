#pragma once

#include "gui_extra.hpp"

#define EXAMPLE_PIC "Example/example1.png"

class Main_Menu : public QWidget {
    public:
        Main_Menu(QWidget *parent = 0);
        ~Main_Menu();
        int Next();
        void Reset();
    private:
        int next;
        QGridLayout *grid;
        QSignalMapper *sigmap;
        QLabel *picture, *title;
        std::vector<QPushButton*> btn;
        std::vector<QLabel*> empty;
};
