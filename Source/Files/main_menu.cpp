#include "../Headers/main_menu.hpp"

Main_Menu::Main_Menu(QWidget* parent) : QWidget(parent)
{
    QGridLayout *grid = new QGridLayout(this);
    grid->setSpacing(50);
    QPushButton *btn;
    QFont font = this->font();
    QSignalMapper *sigmap = new QSignalMapper(this);

    QList<QString> btn_n({"Generate Image", "Generate Pallete", "Exit"});

    for(int i = 0; i < btn_n.size(); ++i){
        btn = new QPushButton(btn_n[i]);
        btn->setFixedSize(300, 100);
        //connect(btn, SIGNAL(clicked()), SLOT(Action()));
        connect(btn, &QPushButton::clicked, this, [this, i]{
            next = (i+1)%3;
            QApplication::quit();
        });
        grid->addWidget(btn, i, 0);
        sigmap->setMapping(btn, i);
    }

    font.setPointSize(15);
    setFont(font);
    next = 0;

}

int Main_Menu::Next()
{
    return next;
}
