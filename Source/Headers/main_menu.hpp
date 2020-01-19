#pragma once

#include "gui_extra.hpp"

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
        std::vector<QPushButton*> btn;
        std::vector<QLabel*> empty;
};
