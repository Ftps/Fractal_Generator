#include "../Headers/mandel.hpp"

int main(int argc, char* argv[])
{
    FILE *fp;
    std::ifstream *fi;
    int a;

    Py_Initialize();
    fp = _Py_fopen((GUI + S"menu.py").c_str(), "r");
    PyRun_SimpleFile(fp, (GUI + S"menu.py").c_str());
    fclose(fp);

    fi = new std::ifstream(MENU);
    *fi >> a;
    delete fi;
    remove(MENU);

    if(a){
        do{
            fp = _Py_fopen((GUI + S"image.py").c_str(), "r");
            PyRun_SimpleFile(fp, (GUI + S"image.py").c_str());
            fclose(fp);
        }while(mandelbrot());
    }
    else{
        fp = _Py_fopen((GUI + S"pallete.py").c_str(), "r");
        PyRun_SimpleFile(fp, (GUI + S"pallete.py").c_str());
    }

    Py_Finalize();

    return 0;
}
