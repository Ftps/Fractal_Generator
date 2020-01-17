#include "../Headers/mandel.hpp"
#include "../Headers/main_menu.hpp"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Main_Menu menu;

    menu.setWindowTitle("Fractal Generator");
    menu.show();
    app.exec();

    if(menu.Next() == 2){
        app.exec();
    }

    return 0;
}
