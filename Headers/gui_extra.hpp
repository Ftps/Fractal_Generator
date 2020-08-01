#pragma once

#define NDEBUG

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
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QColorDialog>
#include <QHeaderView>
#include <QBrush>
#include <vector>
#include <filesystem>
#include <fstream>

// for debug
#include <iostream>
#include <QTextStream>
#include <typeinfo>

#define LOG {std::cout << "IN LINE " << __LINE__ << " OF FILE " << __FILE__ << std::endl; fflush(stdout);}

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

class Line_Popup : public QWidget {
	public:
		Line_Popup(const QString& text, QString* in, QWidget *parent = 0);
		~Line_Popup();
	private:
		QString* in;
		QGridLayout* grid;
		QPushButton *okay, *close;
		QLineEdit* input;
		std::vector<QLabel*> msg;

		void Okay();
		void Close();
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
QTableWidgetItem* new_item(const QString& name);
