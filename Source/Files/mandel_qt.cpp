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

Mandelbrot::Mandelbrot(const Img_Data& img) : Img_Data(img)
{
    map.reserve(res[1]);
    for(int i = 0; i < res[1]; ++i){
        map.push_back(std::vector<int>());
        map[i].reserve(res[0]);
        for(int j = 0; j < res[0]; ++j){
            map[i].push_back(0);
        }
    }
}

void Mandelbrot::run()
{
    if(pp == 2) generate_p2();
}

void Mandelbrot::generate_p2()
{
    long double l, h, b_aux, aux_it;
    std::complex<long double> c_it, c_aux;

    l = LL/zoom;
    h = (res[1]*l)/res[0];

    cc = {cc.real() - l/2, cc.imag() + h/2};
    c_aux = cj;

    for(int i = 0; i < res[1]; ++i){
        b_aux = cc.imag() - i*h/res[1];
        for(int j = 0; j < res[0]; ++j){
            c_it = {cc.real() + j*l/res[0], b_aux};

            if(!Julia){
                c_aux = c_it;
            }

            for(int k = 0; k < it; ++k){
                if(abs2(c_it) > 4){
                    aux_it = log(log(abs2(c_it))/(2*log(2)));
                    map[i][j] = ((k - (int)aux_it)%(color_num-1)) + 1;
                    break;
                }

                c_it = c_aux + (c_it*c_it);

                if(this->k){
                    c_it += this->k/c_it;
                }
            }
        }
    }
    std::cout << "DONE" << std::endl;
}





template<typename T>
T abs2(std::complex<T> c)
{
    return c.real()*c.real() + c.imag()*c.imag();
}
