#include "../Headers/main_menu.hpp"

Main_Menu::Main_Menu(QWidget* parent) : QWidget(parent)
{
    QGridLayout *grid = new QGridLayout(this);
    grid->setSpacing(50);
    QPushButton *btn;
    QFont font = this->font();

    QList<QString> btn_n({"Generate Image", "Generate Pallete", "Exit"});

    btn = new QPushButton(btn_n[0]);
    btn->setFixedSize(300, 100);
    //connect(btn, &QPushButton::clicked, this, &f);
    grid->addWidget(btn, 0, 0);

    btn = new QPushButton(btn_n[1]);
    btn->setFixedSize(300, 100);
    connect(btn, &QPushButton::clicked, this, &Main_Menu::Gen_Pal);
    grid->addWidget(btn, 1, 0);

    btn = new QPushButton(btn_n[2]);
    btn->setFixedSize(300, 100);
    connect(btn, &QPushButton::clicked, this, &QApplication::quit);
    grid->addWidget(btn, 2, 0);


    font.setPointSize(15);
    setFont(font);
    next = 0;

}


void Main_Menu::Action(QString name)
{
    return;
}

void Main_Menu::Gen_Pic()
{
    next = 1;
    QApplication::quit();
}

void Main_Menu::Gen_Pal()
{
    next = 2;
    QApplication::quit();
}

void Main_Menu::Quit()
{
    next = 0;
    QApplication::quit();
}

int Main_Menu::Next()
{
    return next;
}
