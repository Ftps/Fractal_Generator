#pragma once

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <vector>

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
