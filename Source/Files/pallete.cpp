#include "../Headers/pallete.hpp"

const QStringList ll = { "Pallete Name:", "Color to add in HexRGB (#xxxxxx):", "Number of Interpolation Points:" };
const QStringList btn_nn = { "Create Pallete", "Add Color", "Interpolate", "Delete Last", "Exit" };
const QStringList tbl_n = { "Color:", "Number of Iterations:" };
const QStringList tab_i = { "#------", "-" };
const QStringList err_pal = {   "Color format doesn't match.",
                                "Interpolation value must be a positive or null integer.",
                                "Cannot interpolate an empty color.", "Pallete requires a name.",
                                "Pallete requires at least two colors." };

const QBrush white("#ffffff");

Pallete_GUI::Pallete_GUI(QWidget *parent) : QWidget(parent)
{
    grid = new QGridLayout(this);
    QFont font = this->font();

    std::vector<std::function<void()>> funcs;
    funcs.push_back([this]{ CreatePallete(); });
    funcs.push_back([this]{ AddColor(); });
    funcs.push_back([this]{ Interpolate(); });
    funcs.push_back([this]{ if(!clear) Delete(); });
    funcs.push_back([this]{ QApplication::quit(); });

    labels.push_back(new_label(this));
    grid->addWidget(labels.back(), 0, 0);

    for(int i = 0; i < (int)ll.size(); ++i){
        labels.push_back(new_label(this, ll[i], 3));
        grid->addWidget(labels.back(), i+1, 3, 1, 3);
        lines.push_back(new_line(this, 3));
        grid->addWidget(lines.back(), i+1, 6, 1, 3);
    }

    table = new QTableWidget(2, 1, this);
    header = table->verticalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    for(int i = 0; i < 2; ++i){
        table->setItem(i, 0, new_item(tab_i[i]));
    }

    table->setVerticalHeaderLabels(tbl_n);
    grid->addWidget(table, 5, 2, 1, 8);

    for(int i = 0; i < (int)btn_nn.size(); ++i){
        btns.push_back(new_btn(btn_nn[i]));
        connect(btns.back(), &QPushButton::clicked, this, funcs[i]);
        grid->addWidget(btns.back(), 6, 2*i+1, 1, 2);
    }

    labels.push_back(new_label(this));
    grid->addWidget(labels.back(), 7, 11, 1, 1);

    font.setPointSize(13);
    setFont(font);
    setWindowTitle("Pallete Generator");
    clear = true;
}

Pallete_GUI::~Pallete_GUI()
{
    delete grid;
    delete table;
    for(int i = 0; i < (int)labels.size(); ++i){
        delete labels[i];
    }
    for(int i = 0; i < (int)btns.size(); ++i){
        delete btns[i];
    }
    for(int i = 0; i < (int)lines.size(); ++i){
        delete lines[i];
    }
    for(int i = 0; i < (int)colors.size(); ++i){
        delete colors[i];
    }
}

void Pallete_GUI::CreatePallete()
{
    Error_Qt *error;
    QString aux = lines[0]->text();

    if(!aux.size()){
        error = new Error_Qt(err_pal[3]);
        error->show();

        return;
    }

    for(int i = 0; i < aux.size(); ++i){
        if(aux[i] == ' ') aux.replace(i, 1, " ");
    }
    lines[0]->setText(aux);

    if(colors.size() < 2){
        error = new Error_Qt(err_pal[4]);
        error->show();

        return;
    }

    WriteFile();
}

void Pallete_GUI::AddColor()
{
    QColor *color;
    QTableWidgetItem *item;
    Error_Qt *error;
    QBrush *brush;

    color = new QColor(lines[1]->text());

    if(!color->isValid()){
        error = new Error_Qt(err_pal[0]);
        error->show();

        return;
    }

    colors.push_back(color);
    iters.push_back(0);
    brush = new QBrush(*color);

    if(!clear){
        item = new_item(lines[1]->text().toLower());
        item->setBackground(*brush);
        table->insertColumn(table->columnCount());
        table->setItem(0, table->columnCount()-1, item);

        item = new_item(tab_i[1]);
        table->setItem(1, table->columnCount()-1, item);
    }
    else{
        item = table->item(0, 0);
        item->setBackground(*brush);
        item->setText(lines[1]->text());
        clear = false;
    }

    delete brush;
}

void Pallete_GUI::Interpolate()
{
    Error_Qt *error;

    if(clear){
        error = new Error_Qt(err_pal[2]);
        error->show();

        return;
    }
    else if(!isIntegerP(lines[2]->text().toStdString())){
        error = new Error_Qt(err_pal[1]);
        error->show();

        return;
    }

    iters.back() = std::atoi(lines[2]->text().toStdString().c_str());
    if(iters.back()) table->item(1, table->columnCount()-1)->setText(lines[2]->text());
    else table->item(1, table->columnCount()-1)->setText(tab_i[1]);
}

void Pallete_GUI::Delete()
{
    QTableWidgetItem *item;

    if(table->columnCount() > 1){
        table->removeColumn(table->columnCount()-1);
        colors.pop_back();
        iters.pop_back();
    }
    else{
        clear = true;

        for(int i = 0; i < 2; ++i){
            item = table->item(i, 0);
            item->setText(tab_i[i]);
            if(!i) item->setBackground(white);
        }

        colors.pop_back();
        iters.pop_back();
    }
}

void Pallete_GUI::WriteFile()
{
    std::ofstream fp(PAL_PATH + lines[0]->text().toStdString() + PAL_EXT, std::ios::out | std::ios::trunc);
    int num_color = (int)colors.size();
    Error_Qt *error;
    std::array<int, 3> f, l;
    std::array<double, 3> dl;
    QRgb c;
    QColor *cc = new QColor;

    for(int i = 0; i < (int)iters.size(); ++i){
        num_color += iters[i];
    }

    fp << num_color << "\n";

    for(int i = 0; i < (int)colors.size()-1; ++i){
        fp << colors[i]->name().toStdString() << "\n";
        if(iters[i]){
            f = {colors[i]->red(), colors[i]->green(), colors[i]->blue()};
            l = {colors[i+1]->red(), colors[i+1]->green(), colors[i+1]->blue()};
            dl = (l - f)/(double)(iters[i]+1);
            for(int j = 1; j <= iters[i]; ++j){
                c = get_rgb(f + j*dl);
                cc->setRgb(c+ALPHA_CHAN);
                fp << cc->name().toStdString() << "\n";
            }
        }
    }
    fp << colors.back()->name().toStdString();

    fp.close();
    delete cc;

    error = new Error_Qt("Pallete created succesfully!");
    error->show();
}


QRgb get_rgb(const std::array<int, 3> color)
{
    QRgb c = 0;

    for(int i = 0; i < 3; ++i){
        c += color[i]*pow(16, 4-2*i);
    }

    return c;
}
