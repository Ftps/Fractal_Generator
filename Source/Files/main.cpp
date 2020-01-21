#include "../Headers/main_menu.hpp"
#include "../Headers/image_param.hpp"
#include "../Headers/pallete.hpp"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Main_Menu menu;
    Image_Param img;
    Pallete_GUI pal;

    menu.show();
    app.exec();
    menu.hide();

    if(menu.Next() == 1){
        //std::cout << "Running Image Generator . . ." << std::endl;
        img.show();
        app.exec();
        menu.Reset();
    }
    else if(menu.Next() == 2){
        pal.show();
        app.exec();
        menu.Reset();
    }

    return 0;
}
