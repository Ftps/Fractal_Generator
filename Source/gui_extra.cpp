#include "gui_extra.hpp"

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
    msg.back()->setWordWrap(true);
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
    setWindowTitle("Error!");
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

bool isIntegerP(const std::string& s)
{
    if(s.empty()) return false;
    else if(s[0] == '-') return false;
    char *p;
    strtol(s.c_str(), &p, 10);
    return (*p == 0);
}

bool isLDouble(const std::string& s)
{
    if(s.empty()) return false;
    char *p;
    strtold(s.c_str(), &p);
    return (*p == 0);
}

QPushButton* new_btn(const QString& name, int size)
{
    QPushButton *emp = new QPushButton(name);
    emp->setFixedSize(W_X*size, W_Y);

    return emp;
}

QTableWidgetItem* new_item(const QString& name)
{
    QTableWidgetItem *emp = new QTableWidgetItem(name);
    emp->setFlags(emp->flags()^Qt::ItemIsEditable);
    emp->setTextAlignment(Qt::AlignHCenter);

    return emp;
}



Line_Popup::Line_Popup(const QString& text, QString* in, QWidget *parent) : in(in)
{
	grid = new QGridLayout(this);
	QFont font = this->font();

	msg.push_back(new QLabel("", this));
	msg.back()->setFixedSize(W_X/2, W_Y);
	grid->addWidget(msg.back(), 0, 0, 1, 1);

	msg.push_back(new QLabel(text, this));
	msg.back()->setFixedSize(6*W_X, 2*W_Y);
	msg.back()->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
	msg.back()->setWordWrap(true);
	grid->addWidget(msg.back(), 1, 1, 1, 6);

	input = new_line(this, 6);
	grid->addWidget(input, 2, 1, 1, 6);

	msg.push_back(new QLabel("", this));
	msg.back()->setFixedSize(6*W_X, W_Y);
	grid->addWidget(msg.back(), 3, 1, 1, 6);

	okay = new QPushButton("Okay");
	okay->setFixedSize(2*W_X, W_Y);
	connect(okay, &QPushButton::clicked, this, [this]{ Okay(); });
	grid->addWidget(okay, 4, 1, 1, 2);

	close = new QPushButton("Exit");
	close->setFixedSize(2*W_X, W_Y);
	connect(close, &QPushButton::clicked, this, [this]{ Close(); });
	grid->addWidget(close, 4, 5, 1, 2);

	msg.push_back(new QLabel("", this));
	msg.back()->setFixedSize(W_X/2, W_Y);
	grid->addWidget(msg.back(), 5, 7, 1, 1);

	font.setPointSize(15);
	setFont(font);
	setWindowTitle("Input Information");
}

Line_Popup::~Line_Popup()
{
	delete grid;
    delete okay;
	delete close;
	delete input;
    for(int i = 0; i < (int)msg.size(); ++i){
        delete msg[i];
    }
}

void Line_Popup::Okay()
{
	*in = input->text();
	Close();
}

void Line_Popup::Close()
{
	delete this;
}
