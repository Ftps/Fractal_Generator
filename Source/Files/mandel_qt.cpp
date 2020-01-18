#include "../Headers/mandel_qt.hpp"

Pallete::Pallete(const std::string& filename)
{
    std::ifstream fp(filename);
    int aux;
    std::string aux_c;

    fp >> color_num;

    colors.reserve(color_num);
    for(int i = 0; i < color_num; ++i){
        fp >> aux_c;
        colors.push_back(aux_c);
    }

    form = 0;
    aux = color_num-1;

    do{
        aux = aux/16;
        ++form;
    }while(aux != 0);

    fp.close();
}
