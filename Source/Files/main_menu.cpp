#include "../Headers/main_menu.hpp"

QList<QString> btn_n({"Generate Image", "Generate Pallete", "Exit"});

Main_Menu::Main_Menu(QWidget *parent) : QWidget(parent)
{
    grid = new QGridLayout(this);
    grid->setSpacing(50);
    sigmap = new QSignalMapper(this);
    QFont font = this->font();
    QPixmap p(EXAMPLE_PIC);
    QFont f;

    empty.push_back(new_label(this, ""));
    grid->addWidget(empty.back(), 0, 0);

    title = new_label(this, "Fractal Generator", 9, 1);
    f = title->font();
    f.setPointSize(18);
    f.setBold(true);
    title->setFont(f);
    grid->addWidget(title, 1, 1, 1, 9);

    picture = new_label(this, "", 9, 8);
    picture->setPixmap(p.scaled( 16*W_Y, 18*W_X, Qt::KeepAspectRatio, Qt::FastTransformation));
    grid->addWidget(picture, 2, 1, 8, 9);

    for(int i = 0; i < btn_n.size(); ++i){
        btn.push_back(new_btn(btn_n[i]));
        //connect(btn, SIGNAL(clicked()), SLOT(Action()));
        connect(btn.back(), &QPushButton::clicked, this, [this, i]{
            next = (i+1)%3;
            QApplication::quit();
        });
        grid->addWidget(btn.back(), 10, 1+i*3, 1, 2);
        sigmap->setMapping(btn.back(), i);
    }

    empty.push_back(new_label(this, ""));
    grid->addWidget(empty.back(), 11, 9);

    font.setPointSize(13);
    setFont(font);
    setWindowTitle("Fractal Generator");
    next = 0;

}

Main_Menu::~Main_Menu()
{
    delete grid;
    delete sigmap;
    delete picture;
    delete title;
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
