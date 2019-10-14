#include "../Headers/mandel.hpp"

int main(int argc, char* argv[])
{
    FILE *fp;
    int a;

    Py_Initialize();
    fp = _Py_fopen((GUI + S"menu.py").c_str(), "r");
    a = PyRun_SimpleFile(fp, (GUI + S"menu.py").c_str());

    if(a){
        fclose(fp);
        fp = _Py_fopen((GUI + S"pallete.py").c_str(), "r");
        a = PyRun_SimpleFile(fp, (GUI + S"pallete.py").c_str());
        if(a){
            generate_pallete();
        }
    }
    else{
        do{
            fp = _Py_fopen((GUI + S"image.py").c_str(), "r");
            PyRun_SimpleFile(fp, (GUI + S"image.py").c_str());
            fclose(fp);
        }while(mandelbrot());
    }

    Py_Finalize();

    return 0;
}
