#include "../Headers/image_param.hpp"
#include "../Headers/gui_extra.hpp"

const QStringList error_n = {   "Name cannot be empty.", "Real Center must be a number.",
                                "Imaginary Center must be a number.",
                                "Julia Real Center must be a number.",
                                "Julia Imaginary Center must be a number.",
                                "Resolution X must be a positive integer.",
                                "Resolution Y must be a positive integer.",
                                "Zoom must be a number.", "Power must be a number.",
                                "Iterations must be a positive integer.",
                                "Conformal Constant must be a number." };

const QStringList l_name = {    "Pallete:", "Fractal Type:", "Real Center:",
                                "Imaginary Center:", "Julia Real Center:",
                                "Julia Imaginary Center:", "Resolution X:",
                                "Resolution Y:", "Zoom:", "Power:",
                                "Iterations:", "Conformal Constant:"};

const QStringList fractal = { "Mandelbrot Set", "Julia Set" };
const QStringList btns_n = { "Run", "Preview", "Exit" };


Image_Param::Image_Param(QWidget *parent) : QWidget(parent)
{
    grid = new QGridLayout(this);
    QFont font = this->font();

    std::vector<std::function<void()>> funcs;
    funcs.push_back([this]{ Run(); });
    funcs.push_back([this]{ Preview(); });
    funcs.push_back([this]{ QApplication::quit(); });

    labels.push_back(new_label(this));
    grid->addWidget(labels.back(), 0, 0);

    labels.push_back(new_label(this, "Name:", 2));
    grid->addWidget(labels.back(), 1, 1, 1, 2);
    lines.push_back(new_line(this, 7));
    grid->addWidget(lines.back(), 1, 3, 1, 7);

    for(int i = 0; i < l_name.size(); ++i){
        labels.push_back(new_label(this, l_name[i], 2));
        grid->addWidget(labels.back(), i/2+2, 5*(i%2)+1, 1, 2);
        if(i < 2){
            combos.push_back(new QComboBox());
            grid->addWidget(combos.back(), i/2+2, 5*(i%2)+3, 1, 2);
            if(!i){
                combos.back()->addItems(GetPallete());
            }
            else{
                combos.back()->addItems(fractal);
            }
        }
        else{
            lines.push_back(new_line(this));
            grid->addWidget(lines.back(), i/2+2, 5*(i%2)+3, 1, 2);
        }
    }

    prev = new_label(this, "Input parameters and press preview!", 8, 8);
    prev->setStyleSheet("border: 1px solid grey");
    grid->addWidget(prev, 8, 2, 8, 8);

    for(int i = 0; i < btns_n.size(); ++i){
        btns.push_back(new_btn(btns_n[i]));
        grid->addWidget(btns.back(), 16, 4*i+1, 1, 2);
        connect(btns.back(), &QPushButton::clicked, this, funcs[i]);
    }

    labels.push_back(new_label(this, "", 2));
    grid->addWidget(labels.back(), 17, 10, 1, 2);

    font.setPointSize(15);
    setFont(font);
    data = NULL;
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

int Image_Param::InspectValues()
{
    QString aux(lines[0]->text());

    if(!aux.size()){
        return 0;
    }
    for(int i = 0; i < aux.size(); ++i){
        if(aux[i] == " ") aux.replace(i, 1, "_");
    }
    lines[0]->setText(aux);

    for(int i = 1; i < (int)lines.size(); ++i){
        if(i == 5 || i == 6 || i == 9){
            if(!isIntegerP(lines[i]->text().toStdString())) return i;
        }
        else{
            if(!isLDouble(lines[i]->text().toStdString())) return i;
        }
    }

    return -1;
}

void Image_Param::Preview()
{
    QPixmap pic("Images/BO_Splice_center.png");
    int err;
    Error_Qt *error;
    Mandelbrot *mandel;

    if((err = InspectValues()) != -1){
        error = new Error_Qt(error_n[err]);
        error->show();

        return;
    }

    GetImg_Data(true);
    mandel = new Mandelbrot(*data);
    delete mandel;
    delete data;

    prev->clear();
    //prev->setStyleSheet("border-image:url(:/2.png);");
    prev->setPixmap(pic);
    prev->show();
}

void Image_Param::Run()
{
    int err;
    Error_Qt *error;
    Mandelbrot *mandel;

    if((err = InspectValues()) != -1){
        error = new Error_Qt(error_n[err]);
        error->show();

        return;
    }

    GetImg_Data(false);
    mandel = new Mandelbrot(*data);
    mandel->run();
    delete mandel;
    delete data;
}

QStringList Image_Param::GetPallete()
{
    namespace fs = std::filesystem;
    QString aux;
    QStringList pallete = {};

    for(const auto& entry: fs::directory_iterator(PAL_PATH)){
        aux = entry.path().string().c_str();
        aux.remove(0, sizeof(PAL_PATH)-1);
        pallete << aux.remove(aux.size()-sizeof(PAL_EXT)+1, sizeof(PAL_EXT));
    }

    pallete.sort();

    return pallete;
}

void Image_Param::GetImg_Data(bool preview)
{
    std::string filename = combos[0]->currentText().toStdString();

    filename = PAL_PATH + filename + PAL_EXT;
    data = new Img_Data(filename);

    data->name = lines[0]->text().toStdString() + IMG_EXT;

    if(!QString::compare(combos[1]->currentText(), fractal[0])) data->Julia = 0;
    else data->Julia = 1;

    data->cc = {std::stold(lines[1]->text().toStdString()),
                std::stold(lines[2]->text().toStdString())};
    data->cj = {std::stold(lines[3]->text().toStdString()),
                std::stold(lines[4]->text().toStdString())};

    data->res = {std::stoi(lines[5]->text().toStdString()),
                 std::stoi(lines[6]->text().toStdString())};

    data->zoom = pow(10, std::stold(lines[7]->text().toStdString()));
    data->pp = std::stold(lines[8]->text().toStdString());
    data->it = std::stoi(lines[9]->text().toStdString());
    data->k = std::stold(lines[10]->text().toStdString());

    if(preview){
        data->res[1] = XX*((double)data->res[1]/(double)data->res[0]);
        data->res[0] = XX;
    }
}





template<typename T>
QLabel* new_label(T* tt, const QString& name, int length, int heigth)
{
    QLabel *emp = new QLabel(name, tt);
    emp->setFixedSize(W_X*length, W_Y*heigth);
    emp->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    emp->setWordWrap(true);

    return emp;
}

template<typename T>
QLineEdit* new_line(T* tt, int size)
{
    QLineEdit *emp = new QLineEdit(tt);
    emp->setFixedSize(W_X*size, W_Y);

    return emp;
}

QPushButton* new_btn(const QString& name)
{
    QPushButton *emp = new QPushButton(name);
    emp->setFixedSize(W_X*2, W_Y);

    return emp;
}
