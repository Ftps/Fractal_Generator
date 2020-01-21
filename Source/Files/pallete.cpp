#include "../Headers/pallete.hpp"

const QStringList ll = { "Pallete Name:", "Color to add in RGB (#xxxxxx):", "Interpolation Points #:" };
const QStringList btn_nn = { "Create Pallete", "Add Color", "Interpolate", "Delete Last", "Exit" };

Pallete_GUI::Pallete_GUI(QWidget *parent) : QWidget(parent)
{
    grid = new QGridLayout(this);
    QFont font = this->font();

    std::vector<std::function<void()>> funcs;
    funcs.push_back([this]{ CreatePallete(); });
    funcs.push_back([this]{ AddColor(); });
    funcs.push_back([this]{ Interpolate(); });
    funcs.push_back([this]{ Delete(); });
    funcs.push_back([this]{ QApplication::quit(); });

    labels.push_back(new_label(this));
    grid->addWidget(labels.back(), 0, 0);

    for(int i = 0; i < (int)ll.size(); ++i){
        labels.push_back(new_label(this, ll[i], 3));
        grid->addWidget(labels.back(), i+1, 3, 1, 3);
        lines.push_back(new_line(this, 3));
        grid->addWidget(lines.back(), i+1, 6, 1, 3);
    }

    for(int i = 0; i < (int)btn_nn.size(); ++i){
        btns.push_back(new_btn(btn_nn[i]));
        connect(btns.back(), &QPushButton::clicked, this, funcs[i]);
        grid->addWidget(btns.back(), 5, 2*i+1, 1, 2);
    }

    labels.push_back(new_label(this));
    grid->addWidget(labels.back(), 6, 11, 1, 1);

    font.setPointSize(15);
    setFont(font);
}

Pallete_GUI::~Pallete_GUI()
{
    delete grid;
    for(int i = 0; i < (int)labels.size(); ++i){
        delete labels[i];
    }
    for(int i = 0; i < (int)btns.size(); ++i){
        delete btns[i];
    }
    for(int i = 0; i < (int)lines.size(); ++i){
        delete lines[i];
    }
}

void Pallete_GUI::CreatePallete()
{
    return;
}

void Pallete_GUI::AddColor()
{
    return;
}

void Pallete_GUI::Interpolate()
{
    return;
}

void Pallete_GUI::Delete()
{
    return;
}
