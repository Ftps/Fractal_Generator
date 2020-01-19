#include "../Headers/main_menu.hpp"

QList<QString> btn_n({"Generate Image", "Generate Pallete", "Exit"});

Main_Menu::Main_Menu(QWidget *parent) : QWidget(parent)
{
    grid = new QGridLayout(this);
    grid->setSpacing(50);
    sigmap = new QSignalMapper(this);
    QFont font = this->font();

    empty.push_back(new QLabel("", this));
    empty.back()->setFixedSize(50, 50);
    grid->addWidget(empty.back(), 0, 0);

    for(int i = 0; i < btn_n.size(); ++i){
        btn.push_back(new QPushButton(btn_n[i]));
        btn.back()->setFixedSize(300, 100);
        //connect(btn, SIGNAL(clicked()), SLOT(Action()));
        connect(btn.back(), &QPushButton::clicked, this, [this, i]{
            next = (i+1)%3;
            QApplication::quit();
        });
        grid->addWidget(btn.back(), i+1, 1, 1, 2);
        sigmap->setMapping(btn.back(), i);
    }

    empty.push_back(new QLabel("", this));
    empty.back()->setFixedSize(50, 50);
    grid->addWidget(empty.back(), 4, 3);

    font.setPointSize(15);
    setFont(font);
    next = 0;

}

Main_Menu::~Main_Menu()
{
    delete grid;
    delete sigmap;
    for(int i = 0; i < (int)btn.size(); ++i){
        delete btn[i];
    }
    for(int i = 0; i < (int)empty.size(); ++i){
        delete empty[i];
    }
}

int Main_Menu::Next()
{
    return next;
}

void Main_Menu::Reset()
{
    next = 0;
}
