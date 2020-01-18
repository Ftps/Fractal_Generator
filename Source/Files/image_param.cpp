#include "../Headers/image_param.hpp"

QStringList l_name = {  "Pallete:", "Fractal Type:", "Real Center:",
                        "Imaginary Center:", "Julia Real Center:",
                        "Julia Imaginary Center:", "Resolution X:",
                        "Reslution Y:", "Zoom:", "Power:",
                        "Iterations:", "Conformal Constant:"};

QStringList fractal = { "Mandelbrot Set", "Julia Set" };
QStringList btns_n = { "Run", "Preview", "Exit" };


Image_Param::Image_Param(QWidget *parent) : QWidget(parent)
{
    grid = new QGridLayout(this);
    QFont font = this->font();

    std::vector<std::function<void()>> funcs;
    funcs.push_back([this]{ Run(); });
    funcs.push_back([this]{ UpdatePreview(); });
    funcs.push_back([this]{ QApplication::quit(); });

    labels.push_back(new_label());
    grid->addWidget(labels.back(), 0, 0);

    labels.push_back(new_label("Name:", 2));
    grid->addWidget(labels.back(), 1, 1, 1, 2);
    lines.push_back(new_line(7));
    grid->addWidget(lines.back(), 1, 3, 1, 7);

    for(int i = 0; i < l_name.size(); ++i){
        labels.push_back(new_label(l_name[i], 2));
        grid->addWidget(labels.back(), i/2+2, 5*(i%2)+1, 1, 2);
        if(i < 2){
            combos.push_back(new QComboBox());
            grid->addWidget(combos.back(), i/2+2, 5*(i%2)+3, 1, 2);
            if(!i){

            }
            else{
                combos.back()->addItems(fractal);
            }
        }
        else{
            lines.push_back(new_line());
            grid->addWidget(lines.back(), i/2+2, 5*(i%2)+3, 1, 2);
        }
    }

    prev = new_label("Input parameters and press preview!", 8, 8);
    prev->setStyleSheet("border: 1px solid grey");
    grid->addWidget(prev, 8, 2, 8, 8);

    for(int i = 0; i < btns_n.size(); ++i){
        btns.push_back(new_btn(btns_n[i]));
        grid->addWidget(btns.back(), 16, 4*i+1, 1, 2);
        connect(btns.back(), &QPushButton::clicked, this, funcs[i]);
    }

    labels.push_back(new_label("", 2));
    grid->addWidget(labels.back(), 17, 10, 1, 2);

    font.setPointSize(15);
    setFont(font);
}

Image_Param::~Image_Param()
{
    delete grid;
    for(int i = 0; i < (int)labels.size(); ++i){
        delete labels[i];
    }
    for(int i = 0; i < (int)lines.size(); ++i){
        delete lines[i];
    }
    for(int i = 0; i < (int)combos.size(); ++i){
        delete combos[i];
    }
}

QLabel* Image_Param::new_label(QString name, int length, int heigth)
{
    QLabel *emp = new QLabel(name, this);
    emp->setFixedSize(W_X*length, W_Y*heigth);
    emp->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    return emp;
}

QLineEdit* Image_Param::new_line(int size)
{
    QLineEdit *emp = new QLineEdit(this);
    emp->setFixedSize(W_X*size, W_Y);

    return emp;
}

QPushButton* Image_Param::new_btn(QString name)
{
    QPushButton *emp = new QPushButton(name);
    emp->setFixedSize(W_X*2, W_Y);

    return emp;
}

void Image_Param::UpdatePreview()
{
    QPixmap pic("Images/BO_Splice_center.png");

    std::cout << "Updating . . ." << std::endl;
    prev->clear();
    //prev->setStyleSheet("border-image:url(:/2.png);");
    prev->setPixmap(pic);
    prev->show();
}

void Image_Param::Run()
{
    std::cout << "Running . . ." << std::endl;
}

std::string GetCurrentWorkingDir(void)
{
    char buff[FILENAME_MAX];
    GetCurrentDir( buff, FILENAME_MAX );
    std::string current_working_dir(buff);
    return current_working_dir;
}
