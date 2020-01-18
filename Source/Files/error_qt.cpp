#include "../Headers/error_qt.hpp"

Error_Qt::Error_Qt(const QString& err_msg, QWidget *parent) : QWidget(parent)
{
    grid = new QGridLayout(this);
    QFont font = this->font();

    msg.push_back(new QLabel("", this));
    msg.back()->setFixedSize(50, 50);
    grid->addWidget(msg.back(), 0, 0, 1, 1);

    msg.push_back(new QLabel(err_msg, this));
    msg.back()->setFixedSize(300, 100);
    msg.back()->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    grid->addWidget(msg.back(), 1, 1, 1, 6);

    btn = new QPushButton("Okay");
    btn->setFixedSize(100, 50);
    connect(btn, &QPushButton::clicked, this, [this]{ Okay(); });
    grid->addWidget(btn, 2, 3, 1, 2);

    msg.push_back(new QLabel("", this));
    msg.back()->setFixedSize(50, 50);
    grid->addWidget(msg.back(), 3, 7, 1, 1);

    font.setPointSize(15);
    setFont(font);
}

Error_Qt::~Error_Qt()
{
    delete grid;
    delete btn;
    for(int i = 0; i < (int)msg.size(); ++i){
        delete msg[i];
    }
}

void Error_Qt::Okay()
{
    delete this;
}
