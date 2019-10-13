#include "../Headers/mandel.hpp"

int main(int argc, char* argv[])
{
    FILE *fp;
    int a;

    Py_Initialize();

    fp = _Py_fopen((GUI + S"menu.py").c_str(), "r");

    if(PyRun_SimpleFile(fp, (GUI + S"menu.py").c_str())){
        fclose(fp);
        fp = _Py_fopen((GUI + S"pallete.py").c_str(), "r");
        if(PyRun_SimpleFile(fp, (GUI + S"pallete.py").c_str())){
            generate_pallete();
        }
        Py_Finalize();
    }
    else{
        fclose(fp);
        fp = _Py_fopen((GUI + S"image.py").c_str(), "r");
        PyRun_SimpleFile(fp, (GUI + S"image.py").c_str());
        Py_Finalize();
        mandelbrot();
    }

    return 0;
}
