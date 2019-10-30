#include "../Headers/mandel.hpp"

Pallete::Pallete(std::string filename)
{
    std::ifstream fp(filename);
    std::string aux;
    int aux_i;

    fp >> color_num;
    color.reserve(color_num);

    for(int i = 0; i < color_num; ++i){
        fp >> aux;
        color.push_back(aux);
    }

    r = 0;
    aux_i = color_num-1;

    do{
        aux_i = aux_i/16;
        ++r;
    }while(aux_i != 0);

    fp.close();

}

void Pallete::print_pallete(std::ofstream& fp, boost::format fmt)
{

    for(int i = 0; i < color_num; ++i){
        fp << "\"" << fmt % i << " c " << color[i] << "\",\n";
    }
}


Img_Data::Img_Data(int a, int b, std::string img_name)
{
    x = a;
    y = b;
    name = img_name;
}




Image::Image(std::string filename)
{
    std::ifstream fp(filename);
    std::string aux_s, pal;
    int a, b;

    fp >> aux_s;
    fp >> pal;

    c = new Pallete(pal);

    fp >> julia;
    fp >> cc[0];
    fp >> cc[1];

    fp >> a;
    fp >> b;

    img = new Img_Data(a, b, aux_s);

    map.reserve(b);

    for(int i = 0; i < b; ++i){
        map.push_back(vec(int)());
        map[i].reserve(a);
        for(int j = 0; j < a; ++j){
            map[i].push_back(0);
        }
    }

    fp >> z;
    z = pow(10, z);

    fp >> pp;

    fp >> j_c[0];
    fp >> j_c[1];

    fp >> it;
    fp >> con;

    prog = new boost::format("%05.2f");

    if(boost::filesystem::exists(IMAGE + img->name + S".png")){
        aux_s = S"" + img->name;
        std::cout << "\nImage name already exists, numerating . . .";
        for(int i = 1; 1; ++i){
            img->name = aux_s + S"_" + SS(i);
            if(!boost::filesystem::exists(IMAGE + img->name + S".png")){
                break;
            }
        }
        std::cout << "\nImage named as " << img->name << ".png\n";
    }
}

Image::~Image()
{
    delete c;
    delete img;
    delete prog;
}

void Image::progress(int i, int y)
{
    if(i){
        std::cout << "\b\b\b\b\b\b";
    }

    std::cout << *prog % ((100.0*i)/y) << "\%";
    fflush(stdout);

}

void Image::generate_p2(bool preview)
{
    long double a, b, aux_a, ca, cb, x, y, iter, c_x, c_y, b_aux;

    if(preview){
        if(img->x > img->y){
            x = X;
            y = (int)(img->y*(X/img->x));
        }
        else{
            y = X;
            x = (int)(img->x*(X/img->y));
        }
        iter = it/3;
    }
    else{
        x = img->x;
        y = img->y;
        iter = it;
    }

    l = 3/z;
    h = (y*l)/x;

    c_x = cc[0] - l/2;
    c_y = cc[1] + h/2;

    ca = j_c[0];
    cb = j_c[1];

    if(con != 0){
        std::cout << x << " " << y << "\n";
        for(int i = 0; i < y; ++i){
            b_aux = c_y - i*h/y;
            progress(i, y);
            for(int j = 0; j < x; ++j){
                a = c_x + j*l/x;
                b = b_aux;

                if(julia == false){
                    ca = a;
                    cb = b;
                }

                for(int k = 0; k < iter; ++k){
                    if(modu(a, b) > 4){
                        aux_a = log(log(modu(a, b))/(2*log(2)));
                        map[i][j] = ((k - (int)aux_a) % (c->color_num - 1)) + 1;
                        break;
                    }

                    aux_a = ca + a*a - b*b;
                    b = cb + 2*a*b;
                    a = aux_a;

                    // conformal mapping
                    aux_a = con/modu(a, b);
                    a = a*(1+aux_a);
                    b = b*(1-aux_a);
                }
            }
        }
    }
    else{
        for(int i = 0; i < y; ++i){
            b_aux = c_y - i*h/y;
            progress(i, y);
            for(int j = 0; j < x; ++j){
                a = c_x + j*l/x;
                b = b_aux;

                if(julia == false){
                    ca = a;
                    cb = b;
                }

                for(int k = 0; k < it; ++k){
                    if(modu(a, b) > 4){
                        aux_a = log(log(modu(a, b))/(2*log(2)));
                        map[i][j] = ((k - (int)aux_a) % (c->color_num - 1)) + 1;
                        break;
                    }

                    aux_a = ca + a*a - b*b;
                    b = cb + 2*a*b;
                    a = aux_a;
                }
            }
        }
    }

    generate_image(preview);
}

void Image::generate_p3(bool preview)
{
    long double a, b, aux_a, ca, cb, x, y, iter, c_x, c_y, b_aux;

    if(preview){
        if(img->x > img->y){
            x = X;
            y = (int)(img->y*(X/img->x));
        }
        else{
            y = X;
            x = (int)(img->x*(X/img->y));
        }
        iter = it/3;
    }
    else{
        x = img->x;
        y = img->y;
        iter = it;
    }

    l = 3/z;
    h = (y*l)/x;

    c_x = cc[0] - l/2;
    c_y = cc[1] + h/2;

    ca = j_c[0];
    cb = j_c[1];

    if(con != 0){
        for(int i = 0; i < y; ++i){
            b_aux = c_y - i*h/y;
            progress(i, y);
            for(int j = 0; j < x; ++j){
                a = c_x + j*l/x;
                b = b_aux;

                if(julia == false){
                    ca = a;
                    cb = b;
                }

                for(int k = 0; k < iter; ++k){
                    if(modu(a, b) > 4){
                        aux_a = log(log(modu(a, b))/(2*log(2)));
                        map[i][j] = ((k - (int)aux_a) % (c->color_num - 1)) + 1;
                        break;
                    }

                    aux_a = ca + a*(a*a - 3*b*b);
                    b = cb + b*(3*a*a - b*b);
                    a = aux_a;

                    // conformal mapping
                    aux_a = con/modu(a, b);
                    a = a*(1+aux_a);
                    b = b*(1-aux_a);
                }
            }
        }
    }
    else{
        for(int i = 0; i < y; ++i){
            b_aux = c_y - i*h/y;
            progress(i, y);
            for(int j = 0; j < x; ++j){
                a = c_x + j*l/x;
                b = b_aux;

                if(julia == false){
                    ca = a;
                    cb = b;
                }

                for(int k = 0; k < iter; ++k){
                    if(modu(a, b) > 4){
                        aux_a = log(log(modu(a, b))/(2*log(2)));
                        map[i][j] = ((k - (int)aux_a) % (c->color_num - 1)) + 1;
                        break;
                    }

                    aux_a = ca + a*(a*a - 3*b*b);
                    b = cb + b*(3*a*a - b*b);
                    a = aux_a;
                }
            }
        }
    }

    generate_image(preview);
}

void Image::generate_pn(bool preview)
{
    long double a, b, aux_a, ca, cb, mod, x, y, iter, c_x, c_y, b_aux;

    if(preview){
        if(img->x > img->y){
            x = X;
            y = (int)(img->y*(X/img->x));
        }
        else{
            y = X;
            x = (int)(img->x*(X/img->y));
        }
        iter = it/3;
    }
    else{
        x = img->x;
        y = img->y;
        iter = it;
    }

    l = 3/z;
    h = (y*l)/x;

    c_x = cc[0] - l/2;
    c_y = cc[1] + h/2;

    ca = j_c[0];
    cb = j_c[1];

    if(con != 0){
        for(int i = 0; i < y; ++i){
            b_aux = c_y - i*h/y;
            progress(i, y);
            for(int j = 0; j < x; ++j){
                a = c_x + j*l/x;
                b = b_aux;

                if(julia == false){
                    ca = a;
                    cb = b;
                }

                for(int k = 0; k < iter; ++k){
                    if((mod = modu(a, b)) > 4){
                        aux_a = log(log(modu(a, b))/(2*log(2)));
                        map[i][j] = ((k - (int)aux_a) % (c->color_num - 1)) + 1;
                        break;
                    }

                    aux_a = ca + pow(mod, pp/2)*cos(pp*atan(b/a));
                    b = cb + pow(mod, pp/2)*sin(pp*atan(b/a));
                    a = aux_a;

                    // conformal mapping
                    aux_a = con/modu(a, b);
                    a = a*(1+aux_a);
                    b = b*(1-aux_a);
                }
            }
        }
    }
    else{
        for(int i = 0; i < y; ++i){
            b_aux = c_y - i*h/y;
            progress(i, y);
            for(int j = 0; j < x; ++j){
                a = c_x + j*l/x;
                b = b_aux;

                if(julia == false){
                    ca = a;
                    cb = b;
                }

                for(int k = 0; k < iter; ++k){
                    if((mod = modu(a, b)) > 4){
                        aux_a = log(log(modu(a, b))/(2*log(2)));
                        map[i][j] = ((k - (int)aux_a) % (c->color_num - 1)) + 1;
                        break;
                    }
                    /*std::cout << a << " + " << b << "i\n";
                    std::cout << "Mod = " << mod << "\n";
                    std::cout << "Arg = " << atan(b/a) << "\n";
                    getchar();*/
                    aux_a = ca + pow(mod, pp/2.0)*cos(pp*atan(b/a));
                    b = cb + pow(mod, pp/2.0)*sin(pp*atan(b/a));
                    a = aux_a;
                }
            }
        }
    }

    generate_image(preview);
}

void Image::generate_image(bool preview)
{
    std::ofstream fp(IMAGE + ((preview)? S"preview":img->name) + S".xpm", std::ios::out | std::ios::trunc);
    std::string fmt_s = S"%0" + SS(c->r) + S"x";
    boost::format fmt(fmt_s);
    int x, y;

    std::cout << "\n\nImage generation complete, proceeding with writing. . .\n";

    if(preview){
        x = X;
        y = (int)img->y*(X/img->x);
    }
    else{
        x = img->x;
        y = img->y;
    }

    fp << XPM_HEAD + S"\"" + SS(x) + S" " + SS(y) + S" " + SS(c->color_num) + S" " + SS(c->r) + S"\",\n";


    c->print_pallete(fp, fmt);

    for(int i = 0; i < y; ++i){
        fp << "\"";
        for(int j = 0; j < x; ++j){
            fp << fmt % map[i][j];
        }
        if(img->y - i - 1){
            fp << "\",\n";
        }
        else{
            fp << "\"\n};";
        }
    }

    fp.close();

    system((S"convert -quality 100 " + IMAGE + ((preview)? S"preview":img->name) + S".xpm " + IMAGE + ((preview)? S"preview":img->name) + S".png").c_str());
    remove((IMAGE + ((preview)? S"preview":img->name) + S".xpm").c_str());
    std::cout << "Image complete. Exiting program . . .\n";
}

long double Image::power()
{
    return pp;
}

long double Image::modu(long double a, long double b)
{
    return a*a + b*b;
}

void Image::print_param()
{
    std::cout << "Generating Image: " << img->name << "\n";
    if(julia) std::cout << "Fractal Type: Julia Set\n";
    else std::cout << "Fractal Type: Mandelbrot Set\n";
    std::cout << "Power of Polynomial: " << pp << "\n";
    if(julia) std::cout << "Julia constant: " << j_c[0] << " + " << j_c[1] << "i\n";
    if(con != 0) std::cout << "Conformal Scale: " << con << "\n";
    else std::cout << "No conformal mapping\n\n";
    std::cout << "Focus Point: " << cc[0] << " + " << cc[1] << "i\n";
    std::cout << "Zoom level: " << z << "\n";
    std::cout << "Image Size: " << img->x << "x" << img->y << "\n";
    std::cout << "Iterations per Point: " << it << "\n";

    std::cout << "\n\nGenerating Preview . . .:\n";
}

void Image::clear_preview()
{
    int x, y;

    if(img->x > img->y){
        x = X;
        y = (int)(img->y*(X/img->x));
    }
    else{
        y = X;
        x = (int)(img->x*(X/img->y));
    }

    for(int i = 0; i < y; ++i){
        for(int j = 0; j < x; ++j){
            map[i][j] = 0;
        }
    }
}




bool mandelbrot()
{
    Image img(TEMP);
    char c;

    img.print_param();

    if(img.power() == 2) img.generate_p2(true);
    else if(img.power() == 3) img.generate_p3(true);
    else img.generate_pn(true);

    std::cout << "Preview generated. Proceed with full generation? [Y/n] ";
    system((OPEN + S IMAGE + S"preview.png").c_str());
    c = getchar();
    if (c != '\n'){
        while ((getchar()) != '\n');
    }

    remove((IMAGE + S"preview.png").c_str());
    if(c == 'n' || c == 'N') return true;
    else img.clear_preview();

    if(img.power() == 2) img.generate_p2(false);
    else if(img.power() == 3) img.generate_p3(false);
    else img.generate_pn(false);

    return false;
}
