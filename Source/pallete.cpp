#include "pallete.hpp"

const QStringList btn_nn = { "Create Pallete", "Add Color", "Interpolate", "Delete Last", "Exit" };
const QStringList tbl_n = { "Color:", "Number of Iterations:" };
const QStringList tab_i = { "#------", "-" };
const QStringList err_pal = {   "Pallete requires at least two colors.",
								"Pallete requires a name.",
								"Interpolation requires a color.",
								"Interpolation value must be a positive or null integer." };

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
    for(int i = 0; i < (int)colors.size(); ++i){
        delete colors[i];
    }
}

void Pallete_GUI::CreatePallete()
{
    Error_Qt *error;
    QString *aux = new QString("");
	Line_Popup *getName;

	if(colors.size() < 2){
		error = new Error_Qt(err_pal[0]);
		error->show();

		return;
	}

	getName = new Line_Popup("Enter the name of the pallete:", aux);
	getName->show();

	QEventLoop loop;
	connect(getName, SIGNAL(destroyed()), &loop, SLOT(quit()));
	loop.exec();

    if(!aux->size()){
        error = new Error_Qt(err_pal[1]);
        error->show();

        return;
    }

    for(int i = 0; i < aux->size(); ++i){
        if((*aux)[i] == ' ') aux->replace(i, 1, "_");
    }

    WriteFile(aux->toStdString());
	delete aux;
}

void Pallete_GUI::AddColor()
{
    QColor *color;
    QTableWidgetItem *item;
    QBrush *brush, *textBrush;

    color = new QColor(QColorDialog::getColor(Qt::white, this));

    if(!color->isValid()) return;

    colors.push_back(color);
    iters.push_back(0);
    brush = new QBrush(*color);
	textBrush = new QBrush(QColor(255 - color->red(), 255 - color->blue(), 255 - color->green()));

    if(!clear){
        item = new_item(color->name(QColor::HexRgb));
        item->setBackground(*brush);
		item->setForeground(*textBrush);
        table->insertColumn(table->columnCount());
        table->setItem(0, table->columnCount()-1, item);

        item = new_item(tab_i[1]);
        table->setItem(1, table->columnCount()-1, item);
    }
    else{
        item = table->item(0, 0);
        item->setBackground(*brush);
		item->setForeground(*textBrush);
        item->setText(color->name(QColor::HexRgb));
        clear = false;
    }

    delete brush;
	delete textBrush;
}

void Pallete_GUI::Interpolate()
{
    Error_Qt *error;
	Line_Popup* getInter;
	QString* inter = new QString("");

    if(clear){
        error = new Error_Qt(err_pal[2]);
        error->show();

        return;
    }

	getInter = new Line_Popup("Interpolation number (must be positive):", inter);
	getInter->show();

	QEventLoop loop;
    connect(getInter, SIGNAL(destroyed()), &loop, SLOT(quit()));
    loop.exec();

	if(!isIntegerP(inter->toStdString())){
		error = new Error_Qt(err_pal[3]);
        error->show();
		return;
	}

    iters.back() = std::atoi(inter->toStdString().c_str());
	if(iters.back()) table->item(1, table->columnCount()-1)->setText(*inter);
    else table->item(1, table->columnCount()-1)->setText(tab_i[1]);

	delete inter;
}

void Pallete_GUI::Delete()
{
    QTableWidgetItem *item;

    if(table->columnCount() > 1){
        table->removeColumn(table->columnCount()-1);
    }
    else{
        clear = true;

        for(int i = 0; i < 2; ++i){
            item = table->item(i, 0);
            item->setText(tab_i[i]);
			if(!i){
				item->setForeground(Qt::white);
				item->setBackground(QColor("#00FFFFFF"));
			}
        }
    }
	colors.pop_back();
	iters.pop_back();
}

void Pallete_GUI::WriteFile(const std::string& aux)
{
    std::ofstream fp(PAL_PATH + aux + PAL_EXT, std::ios::out | std::ios::trunc);
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
