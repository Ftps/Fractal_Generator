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
        colors.push_back(new QColor(aux_c.c_str()));
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

    if(pp == 2) generate_p2();
    else if(pp == 3) generate_p3();
    else generate_pn();

    draw_image();
}

void Mandelbrot::generate_p2()
{
    long double l, h, b_aux, aux_it, a, b;
    std::array<long double, 2> c_aux;

    l = LL/zoom;
    h = (res[1]*l)/res[0];

    cc = {cc.real() - l/2, cc.imag() + h/2};
    c_aux = {cj.real(), cj.imag()};

    if(this->k){
        for(int i = 0; i < res[1]; ++i){
            b_aux = cc.imag() - i*h/res[1];
            for(int j = 0; j < res[0]; ++j){
                a = cc.real() + j*l/res[0];
                b = b_aux;

                if(!Julia){
                    c_aux[0] = a;
                    c_aux[1] = b;
                }

                for(int k = 0; k < it; ++k){
                    if(abs1(a,b) > 4){
                        aux_it = log(log(abs1(a,b))/(2*log(2)));
                        map[i][j] = ((k - (int)aux_it)%(color_num-1)) + 1;
                        break;
                    }

                    aux_it = a;
                    a = c_aux[0] + a*a - b*b;
                    b = c_aux[1] + 2*aux_it*b;

                    aux_it = this->k/abs1(a,b);
                    a = a*(a+aux_it);
                    b = b*(a-aux_it);
                }
            }
        }
    }
    else{
        for(int i = 0; i < res[1]; ++i){
            b_aux = cc.imag() - i*h/res[1];
            for(int j = 0; j < res[0]; ++j){
                a = cc.real() + j*l/res[0];
                b = b_aux;

                if(!Julia){
                    c_aux[0] = a;
                    c_aux[1] = b;
                }

                for(int k = 0; k < it; ++k){
                    if(abs1(a,b) > 4){
                        aux_it = log(log(abs1(a,b))/(2*log(2)));
                        map[i][j] = ((k - (int)aux_it)%(color_num-1)) + 1;
                        break;
                    }

                    aux_it = a;
                    a = c_aux[0] + a*a - b*b;
                    b = c_aux[1] + 2*aux_it*b;
                }
            }
        }
    }
}

void Mandelbrot::generate_p3()
{
    long double l, h, b_aux, aux_it, a, b;
    std::array<long double, 2> c_aux;

    l = LL/zoom;
    h = (res[1]*l)/res[0];

    cc = {cc.real() - l/2, cc.imag() + h/2};
    c_aux = {cj.real(), cj.imag()};

    if(this->k){
        for(int i = 0; i < res[1]; ++i){
            b_aux = cc.imag() - i*h/res[1];
            for(int j = 0; j < res[0]; ++j){
                a = cc.real() + j*l/res[0];
                b = b_aux;

                if(!Julia){
                    c_aux[0] = a;
                    c_aux[1] = b;
                }

                for(int k = 0; k < it; ++k){
                    if(abs1(a,b) > 4){
                        aux_it = log(log(abs1(a,b))/(2*log(2)));
                        map[i][j] = ((k - (int)aux_it)%(color_num-1)) + 1;
                        break;
                    }

                    aux_it = a;
                    a = c_aux[0] + a*(a*a - 3*b*b);
                    b = c_aux[1] + b*(3*aux_it*aux_it - b*b);

                    aux_it = this->k/abs1(a,b);
                    a = a*(a+aux_it);
                    b = b*(a-aux_it);
                }
            }
        }
    }
    else{
        for(int i = 0; i < res[1]; ++i){
            b_aux = cc.imag() - i*h/res[1];
            for(int j = 0; j < res[0]; ++j){
                a = cc.real() + j*l/res[0];
                b = b_aux;

                if(!Julia){
                    c_aux[0] = a;
                    c_aux[1] = b;
                }

                for(int k = 0; k < it; ++k){
                    if(abs1(a,b) > 4){
                        aux_it = log(log(abs1(a,b))/(2*log(2)));
                        map[i][j] = ((k - (int)aux_it)%(color_num-1)) + 1;
                        break;
                    }

                    aux_it = a;
                    a = c_aux[0] + a*(a*a - 3*b*b);
                    b = c_aux[1] + b*(3*aux_it*aux_it - b*b);
                }
            }
        }
    }
}

void Mandelbrot::generate_pn()
{
    long double l, h, aux_it, b_aux;
    std::complex<long double> c_aux, c_it;

    l = LL/zoom;
    h = (res[1]*l)/res[0];

    cc = {cc.real() - l/2, cc.imag() + h/2};
    c_aux = cj;

    if(this->k){
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

                    c_it = c_aux + pow(c_it, pp);

                    c_it += this->k/c_it;
                }
            }
        }
    }
    else{
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

                    c_it = c_aux + pow(c_it, pp);
                }
            }
        }
    }
}

void Mandelbrot::draw_image()
{
    QPainter paint;
    image = new QImage(res[0], res[1], QImage::Format_RGB32);
    image->fill(*colors[0]);
    QPen pen;

    paint.begin(image);
    paint.setRenderHint(QPainter::Antialiasing, true);
    pen.setWidth(1);

    for(int i = 0; i < res[0]; ++i){
        for(int j = 0; j < res[1]; ++j){
            if(map[j][i]){
                pen.setColor(*colors[map[j][i]]);
                paint.setPen(pen);
                paint.drawPoint(i, j);
            }
        }
    }
    paint.end();

    if(!preview) image->save((IMG_PATH+name).c_str());
}

QImage Mandelbrot::get_image()
{
    return *image;
}



template<typename T>
T abs2(std::complex<T> c)
{
    return c.real()*c.real() + c.imag()*c.imag();
}

inline long double abs1(long double a, long double b)
{
    return a*a + b*b;
}
