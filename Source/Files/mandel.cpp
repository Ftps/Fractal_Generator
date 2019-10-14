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

    if(julia == true){
        fp >> j_c[0];
        fp >> j_c[1];
    }

    fp >> it;
    fp >> con;
    remove(filename.c_str());
}

Image::~Image()
{
    delete c;
    delete img;
}

void Image::generate_p2(bool preview)
{
    long double a, b, aux_a, ca, cb, x, y, iter, c_x, c_y;

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
        std::cout << "CONFORMAL GENERATION\n2 POWER\n";
        std::cout << x << " " << y << "\n";
        for(int i = 0; i < y; ++i){
            for(int j = 0; j < x; ++j){
                a = c_x + j*l/x;
                b = c_y - i*h/y;

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
        std::cout << "NON CONFORMAL GENERATION\n2 POWER\n";
        for(int i = 0; i < y; ++i){
            for(int j = 0; j < x; ++j){
                a = c_x + j*l/x;
                b = c_y - i*h/y;

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
    long double a, b, aux_a, ca, cb, x, y, iter, c_x, c_y;

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
        std::cout << "CONFORMAL GENERATION\n3 POWER\n";
        for(int i = 0; i < y; ++i){
            for(int j = 0; j < x; ++j){
                a = c_x + j*l/x;
                b = c_y - i*h/y;

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
        std::cout << "NON CONFORMAL GENERATION\n3 POWER\n";
        for(int i = 0; i < y; ++i){
            for(int j = 0; j < x; ++j){
                a = c_x + j*l/x;
                b = c_y - i*h/y;

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
    long double a, b, aux_a, ca, cb, mod, x, y, iter, c_x, c_y;

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
        std::cout << "CONFORMAL GENERATION\nN POWER\n";
        for(int i = 0; i < y; ++i){
            for(int j = 0; j < x; ++j){
                a = c_x + j*l/x;
                b = c_y - i*h/y;

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
        std::cout << "NON CONFORMAL GENERATION\nN POWER\n";
        for(int i = 0; i < y; ++i){
            for(int j = 0; j < x; ++j){
                a = c_x + j*l/x;
                b = c_y - i*h/y;

                if(julia == false){
                    ca = a;
                    cb = b;
                }

                for(int k = 0; k < iter; ++k){
                    if(mod = modu(a, b) > 4){
                        aux_a = log(log(modu(a, b))/(2*log(2)));
                        map[i][j] = ((k - (int)aux_a) % (c->color_num - 1)) + 1;
                        break;
                    }

                    aux_a = ca + pow(mod, pp/2)*cos(pp*atan(b/a));
                    b = cb + pow(mod, pp/2)*sin(pp*atan(b/a));
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

    std::cout << "Image generation complete, proceeding with writing. . .\n";

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




void generate_pallete()
{
    std::string name;
    mat(int) colors;
    int c_num, p_num;
    vec(int) aux;
    boost::format fmt("%02x");

    aux.reserve(3);

    std::cout << "Write a color name (no whitespaces): ";
    std::cin >> name;

    std::ofstream fp(PALLETE + name + S".pl", std::ios::out | std::ios::trunc);

    std::cout << "Input the total number of colors: ";
    std::cin >> c_num;
    std::cout << "Input the number of fixed points: ";
    std::cin >> p_num;

    colors.reserve(p_num);

    for(int i = 0; i < p_num; ++i){
        colors.push_back(vec(int)());
        colors[i].reserve(3);
        std::cout << "Input color " << i << " in HEX with spaces (FF FF FF): ";
        for(int j = 0; j < 3; ++j){
            std::cin >> std::hex >> colors[i][j];
            if(!i) aux.push_back(0);
        }
    }

    /*std::cout << "\n\nFilename: " << name << "\n";
    std::cout << "Total Number of Colors: " << c_num << "\n";
    std::cout << "Fixed Points: " << p_num << "\n";

    for(int i = 0; i < p_num; ++i){
        std::cout << "Color " << i << ": ";
        for(int j = 0; j < 3; ++j) std::cout << colors[i][j] << " ";
        std::cout << "\n";
    }*/

    c_num = (c_num - p_num)/p_num;

    fp << c_num*p_num + 1<< "\n#000000\n";

    for(int i = 1; i <= p_num; ++i){
        for(int j = 0; j < 3; ++j){
            aux[j] = colors[i%p_num][j] - colors[i-1][j];
        }

        for(int k = 0; k < c_num; ++k){
            fp << "#";
            for(int j = 0; j < 3; ++j){
                fp << fmt % (int)(colors[i-1][j] + aux[j]*k/c_num);
            }
            fp << "\n";
        }

    }

    fp.close();

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
    fflush(stdout);
    c = getchar();
    remove((IMAGE + S"preview.png").c_str());
    if(c == 'n' || c == 'N') return true;
    else img.clear_preview();

    if(img.power() == 2) img.generate_p2(false);
    else if(img.power() == 3) img.generate_p3(false);
    else img.generate_pn(false);

    return false;
}
