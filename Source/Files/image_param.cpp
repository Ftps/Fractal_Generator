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

const QStringList l_name = {    "Pallete:", "Fractal Type:", "Zoom:",
                                "Real Center:", "Imaginary Center:",
                                "Power:", "Julia Real Center:",
                                "Julia Imaginary Center:", "Iterations:",
                                "Resolution X:", "Resolution Y:",
                                "Conformal Constant:"};

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
    lines.push_back(new_line(this, 10));
    grid->addWidget(lines.back(), 1, 3, 1, 10);

    for(int i = 0; i < l_name.size(); ++i){
        labels.push_back(new_label(this, l_name[i], 2));
        grid->addWidget(labels.back(), i/3+2, 4*(i%3)+1, 1, 2);
        if(i < 2){
            combos.push_back(new QComboBox());
            grid->addWidget(combos.back(), i/3+2, 4*(i%3)+3, 1, 2);
            if(!i){
                combos.back()->addItems(GetPallete());
            }
            else{
                combos.back()->addItems(fractal);
            }
        }
        else{
            lines.push_back(new_line(this));
            grid->addWidget(lines.back(), i/3+2, 4*(i%3)+3, 1, 2);
        }
    }

    labels.push_back(new_label(this, "", 12));
    grid->addWidget(labels.back(), 8, 1, 1, 12);

    prev = new_label(this, "Input parameters and press preview!", 7, 7);
    prev->setStyleSheet("border: 1px solid grey");
    grid->addWidget(prev, 9, 4, 7, 7);

    current = new_label(this, "", 7, 1);
    grid->addWidget(current, 16, 4, 1, 7);

    prog = new QProgressBar();
    prog->setValue(0);
    prog->setTextVisible(true);
    grid->addWidget(prog, 17, 4, 1, 7);

    for(int i = 0; i < btns_n.size(); ++i){
        btns.push_back(new_btn(btns_n[i], (i == 1) ? 3 : 2));
        connect(btns.back(), &QPushButton::clicked, this, funcs[i]);
    }
    grid->addWidget(btns[0], 18, 3, 1, 2);
    grid->addWidget(btns[1], 18, 6, 1, 3);
    grid->addWidget(btns[2], 18, 10, 1, 2);

    labels.push_back(new_label(this, "", 2));
    grid->addWidget(labels.back(), 19, 13, 1, 2);

    font.setPointSize(13);
    setFont(font);
    setWindowTitle("Fractal Generator");
    data = NULL;
    m = NULL;
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
        if(i == 7 || i == 8 || i == 9){
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
    int err;

    if(m == NULL){
        if((err = InspectValues()) != -1){
            error = new Error_Qt(error_n[err]);
            error->show();

            return;
        }

        auto f = [this]{
            Mandelbrot *mandel;

            GetImg_Data(true);
            mandel = new Mandelbrot(*data);
            Connect(mandel);
            mandel->run();

            prev->clear();
            prev->setPixmap(QPixmap::fromImage(mandel->get_image(), Qt::AutoColor));
            prev->show();

            delete mandel;
            delete data;

            m = NULL;
        };

        m = new std::thread(f);
        m->detach();
    }
}

void Image_Param::Run()
{
    int err;

    if(m == NULL){
        if((err = InspectValues()) != -1){
            error = new Error_Qt(error_n[err]);
            error->show();

            return;
        }

        auto f = [this]{
            Mandelbrot *mandel;

            GetImg_Data(false);
            mandel = new Mandelbrot(*data);
            Connect(mandel);
            mandel->run();
            delete mandel;
            delete data;

            m = NULL;
        };

        m = new std::thread(f);
        m->detach();
    }
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

    if(!QString::compare(combos[1]->currentText(), fractal[0])) data->Julia = false;
    else data->Julia = true;

    data->zoom = pow(10, std::stold(lines[1]->text().toStdString()));

    data->cc = {std::stold(lines[2]->text().toStdString()),
                std::stold(lines[3]->text().toStdString())};
    data->pp = std::stold(lines[4]->text().toStdString());

    if(data->Julia){
    data->cj = {std::stold(lines[5]->text().toStdString()),
                std::stold(lines[6]->text().toStdString())};
    }
    else data->cj = 0;
    data->it = std::stoi(lines[7]->text().toStdString());

    data->res = {std::stoi(lines[8]->text().toStdString()),
                 std::stoi(lines[9]->text().toStdString())};
    data->k = std::stold(lines[10]->text().toStdString());

    if(preview){
        data->preview = true;
        data->res[1] = XX*((double)data->res[1]/(double)data->res[0]);
        data->res[0] = XX;
    }
    else data->preview = false;
}

void Image_Param::getProg(int value)
{
    prog->setValue(value);
}

void Image_Param::getCurr(QString doing)
{
    current->setText(doing);
}

void Image_Param::Connect(Mandelbrot *mandel)
{
    connect(mandel, &Mandelbrot::progress, this, &Image_Param::getProg);
    connect(mandel, &Mandelbrot::current, this, &Image_Param::getCurr);
}
