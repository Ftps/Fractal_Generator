#include "../Headers/mandel_qt.hpp"
#include "../Headers/main_menu.hpp"
#include "../Headers/image_param.hpp"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Main_Menu menu;
    Image_Param img;

    menu.setWindowTitle("Fractal Generator");

    do{
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
            std::cout << "Running Pallete Generator . . ." << std::endl;
            menu.Reset();
        }
    }while(menu.Next());

    return 0;
}
