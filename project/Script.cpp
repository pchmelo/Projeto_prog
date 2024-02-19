#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"

using namespace std;

namespace prog {
    // Use to read color values from a script file.
    istream& operator>>(istream& input, Color& c) {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string& filename) :
        image(nullptr), input(filename) {}

    void Script::clear_image_if_any() {
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
    }
    Script::~Script() {
        clear_image_if_any();
    }

    void Script::run() {
        string command;
        while (input >> command) {
            cout << "Executing command '" << command << "' ..." << endl;
            if (command == "open") {
                open();
                continue;
            }
            if (command == "blank") {
                blank();
                continue;
            }
            // Other commands require an image to be previously loaded.
            if (command == "save") {
                save();
                continue;
            }

            if (command == "to_gray_scale"){
                to_gray_scale();
                continue;
            } 

            if (command == "crop"){
                crop();
                continue;
            }

            if (command == "invert"){
                invert();
                continue;
            }

            if (command == "replace"){
                replace();
                continue;
            }

            if (command == "fill"){
                fill();
                continue;
            }

            if (command == "h_mirror"){
                h_mirror();
                continue;
            }

            if (command == "v_mirror"){
                v_mirror();
                continue;
            }

            if (command == "add"){
                add();
                continue;
            }

            if (command == "rotate_left"){
                rotate_left();
                continue;
            }

            if (command == "rotate_right"){
                rotate_right();
                continue;
            }

            if (command == "median_filter"){
                median_filter();
                continue;
            }
            if (command == "xpm2_open"){
                xpm2_open();
                continue;
            }
            if (command == "xpm2_save"){
                xpm2_save();
                continue;
            }

            // TODO ...

        }
    }
    void Script::open() {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }
    void Script::blank() {
        // Replace current image (if any) with blank image.
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }
    void Script::save() {
        // Save current image to PNG file.
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }
    void Script::to_gray_scale() {    //implementação da função to_gray_scale()
        int w = image->width();
        int h = image->height();
        
        rgb_value v;
        Color ponto;

        for (int i = 0; i < h; i++){                                    //for loops que percorrem a matriz que representa a imagem
            for (int j = 0; j < w; j++){
                ponto = image -> at(j,i);                               //guardar na variável ponto a cor que encontra-se no pixel (j,i)
                v = (ponto.red() + ponto.green() + ponto.blue()) / 3;

                ponto.red() = v;                                        //
                ponto.green() = v;                                      //atribuir ao (r, g, b) do ponto o valor de v
                ponto.blue() = v;                                       //

                image -> at(j,i) = ponto;                               //atribuir ao pixel (j,i) a nova cor atribuida ao ponto
            }
        }
    }
                              
    void Script::crop(){    //implementação da função crop()
        int x, y, w, h;
        input >> x >> y >> w >> h;                                      //receber input das coordenadas do pixel que representa o canto superior esquerdo de um retângulo além da sua width_ e height_ 

        Image new_img(w, h);                                            //criação de uma nova matriz que representará a área em que o crop() é aplicado

        for (int i = y; i < (y + h); i++){                              //for loops que percorrem a matriz que representa a imagem apenas na área em que o crop() é aplicado
            for (int j = x; j < (x + w); j++){
                new_img.at(j-x, i-y) = image -> at(j,i);                //atribuição no pixel (j-x,i-y) da cor que se encontra no pixel (j,i)
            }
        }

        *image = new_img;                                               //atribuição dos valores contidos em new_img à imagem
    }

    void Script::invert() {    //implementação da função invert()
        int w = image->width();
        int h = image->height();

        Color ponto;

        for (int i = 0; i < h; i++){                                    //for loops que percorrem a matriz que representa a imagem
            for (int j = 0; j < w; j++){
                ponto = image -> at(j,i);                               //guardar na variável ponto a cor que se encontra no pixel (j,i)

                ponto.red() = 255 - ponto.red();                        //
                ponto.green() = 255 - ponto.green();                    //atribuir ao (r, g, b) do ponto o inverso da sua cor
                ponto.blue() = 255 - ponto.blue();                      //

                image -> at(j,i) = ponto;                               //atribuir ao pixel (j,i) a nova cor atribuida ao ponto
            }
        }
    }

    void Script::replace(){    //implementação da função replace()
        int w = image->width();
        int h = image->height();

        int r1, g1, b1, r2, g2, b2;

        input >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;                      //receber input aos rgb_values de cor_1 e cor_2
        
        Color cor_1(r1,g1,b1);                                          //atribuição dos rgb_values recebidos anteriormente à cor_1
        Color cor_2(r2,g2,b2);                                          //atribuição dos rgb_values recebidos anteriormente à cor_2

        for (int i = 0; i < h; i++){                                    //for loops que percorrem matriz que representa a imagem
            for (int j = 0; j < w; j++){
                if (image -> at(j,i).compare_color(cor_1)){             //if que compara a cor do pixel (j,i) com a cor_1
                    image -> at(j,i) = cor_2;                           //no caso das cores serem iguais, troca a cor do pixel (j,i) pela cor_2
                }
            }
        }
    }

    void Script::fill(){    //implementação da função fill()
        int x, y, w, h, r, g, b;
        input >> x >> y >> w >> h >> r >> g >> b;                       //receber input aos valores das coordenadas (x,y) do canto superior esquerdo de um retângulo com h de height_ e w de width_ e os valores (r,g,b) da cor

        Color cor(r,g,b);                                               //atribuição dos rgb_values recebidos anteriormente à cor

        for (int i = y; i < (y + h); i++){                              //for loops que percorrem o retângulo
            for (int j = x; j < (x + w); j++){
                image -> at(j,i) = cor;                                 //atribuir ao pixel (j,i) do retângulo a cor atribuida
            }
        }
    }

    void Script::h_mirror(){    //implementação da função h_mirror()
        int w, h;
        Color ponto;

        w = image->width();
        h = image->height();

        for (int i = 0; i < h; i++){                                    //for loops que percorrem a matriz que representa a imagem
            for (int j = 0; j < (w/2); j++){
                ponto = image->at(w-1-j, i);

                image->at(w-1-j, i) = image->at(j,i);                   //espelhar a parte direita da imagem
                image->at(j,i) = ponto;                                 //espelhar a parte esquerda da imagem
            }
        }
    }

    void Script::v_mirror(){    //implementação da função v_mirror()
        int w, h;
        Color ponto;

        w = image->width();
        h = image->height();

        for (int i = 0; i < (h/2); i++){                                //for loops que percorrem a matriz que representa a imagem
            for (int j = 0; j < w; j++){
                ponto = image->at(j, h-1-i);

                image->at(j, h-1-i) = image->at(j,i);                   //espelhar a parte inferior da imagem
                image->at(j,i) = ponto;                                 //espelhar a parte superior da imagem 
            }
        }
    }

    void Script::add(){    //implementação da função add()
        string filename;
        int w, h, r, g, b, x, y;

        w = image->width();
        h = image->height();

        Image new_img(*image);                                          //criação de uma nova imagem igual à imagem atual

        input >> filename >> r >> g >> b >> x >> y;                     //receber input ao filename e as componentes (r,g,b) da cor a evitar
        clear_image_if_any();                                           //apagar a imagem atual
        image = loadFromPNG(filename);                                  //tornar a imagem atual na imagem contida em filename

        w = image->width();
        h = image->height();

        Color cor(r,g,b);                                               //atribuição dos rgb_values recebidos anteriormente à cor

        for (int i = y; i < y + h; i++){                                //for loops que percorrem a matriz que representa a nova imagem
            for (int j = x; j < x + w; j++){
                if (!(image->at(j-x, i-y).compare_color(cor))){         //comparação entre a cor da imagem atual e a cor
                    new_img.at(j,i) = image->at(j-x, i-y);              //no caso das cores serem diferentes atribui ao pixel (j,i) da nova imagem o pixel da imagem atual comparado anteriormente
                }
            }
        }

        *image = new_img;
    }

    void Script::rotate_left(){    //implementação da função rotate_left()
        int w, h;

        w = image->width();
        h = image->height();

        Image new_img(h,w);                                             //criação de uma nova imagem com width_ igual a height da imagem atual e vice-versa

        for (int i = 0; i < h; i++){                                    //for loops que percorrem a matriz que representa a imagem
            for (int j = 0; j < w; j++){
                new_img.at(i, w-1-j) = image->at(j,i);                  //atribuir à nova imagem a imagem atual rotacionada 90º para a esquerda
            }
        }

        *image = new_img;                                               //atribuição dos valores contidos em new_img à imagem
    }

    void Script::rotate_right(){    //implementação da função rotate_right()
        int w, h;

        w = image->width();
        h = image->height();

        Image new_img(h,w);                                             //criação de uma nova imagem com width_ igual a height da imagem atual e vice-versa

        for (int i = 0; i < h; i++){                                    //for loops que percorrem a matriz que representa a imagem
            for (int j = 0; j < w; j++){
                new_img.at(h-1-i, j) = image->at(j,i);                  //atribuir à nova imagem a imagem atual rotacionada 90º para a direita
            }
        }

        *image = new_img;                                               //atribuição dos valores contidos em new_img a imagem
    }

    void Script::median_filter(){    //implementação da função median_filter()
        int ws, w, h, center, nh_col, nh_ln, n_pix = 0;
        Color median;

        Image new_img(*image);                                          //criação de uma nova imagem com as mesmas proporções da imagem atual

        vector <int> val_r;
        vector <int> val_g;
        vector <int> val_b;

        w = image->width();
        h = image->height();

        input >> ws;                                                    //recebe input ao size da window

        center = (ws - 1)/2;                                            //calculo para obter o centro da window

        for (int i = 0; i < h; i++){                                    //for loops que percorrem a matriz que representa a imagem
            for (int j = 0; j < w; j++){

                for (int k = -center; k <= center; k++){                //for loops que percorrem os pixeis dentro da window centrada no ponto (j,i)
                    for (int l = -center; l <= center; l++){
                        nh_ln = i + k;                                  //Calculo da neighbourhood que limita as linhas
                        nh_col = j + l;                                 //Calculo da neighbourhood que limita as colunas

                        if((nh_ln >= 0) && (nh_col >= 0) && (nh_ln < h) && (nh_col < w)){    //if que limita o acesso aos pixeis da window

                            val_r.push_back(new_img.at(nh_col,nh_ln).red());                 //
                            val_g.push_back(new_img.at(nh_col,nh_ln).green());               //atribuição dos valores rgb dos pixeis em vetors
                            val_b.push_back(new_img.at(nh_col,nh_ln).blue());                //
                            n_pix++;
                        }
                    }
                }
                sort(val_r.begin(), val_r.end());                       //
                sort(val_g.begin(), val_g.end());                       //sorting dos valores rgb guardados nos vetores
                sort(val_b.begin(), val_b.end());                       //

                if (n_pix % 2 != 0){
                    median.red() = val_r.at(n_pix/2);                   //
                    median.green() = val_g.at(n_pix/2);                 //Calculo da mediana caso o número de pixéis no vetor seja impar
                    median.blue() = val_b.at(n_pix/2);                  //
                }
                else{
                    median.red() = (val_r.at((n_pix/2)) + val_r.at((n_pix-1) /2)) / 2;      //
                    median.green() = (val_g.at((n_pix/2)) + val_g.at((n_pix-1) /2)) / 2;    //Calculo da mediana caso o número de pixéis no vetor seja par
                    median.blue() = (val_b.at((n_pix/2)) + val_b.at((n_pix-1) /2)) / 2;     //
                }

                image->at(j,i) = median;                                //atribuição do valor da mediana ao pixel (j,i)

                n_pix = 0;
                val_r.clear();                                          //
                val_g.clear();                                          //limpa os valores contidos no vetor
                val_b.clear();                                          //
            }
        }
    }

    void Script::xpm2_open(){    //implementação da função xpm2_open()
        clear_image_if_any();                                           //limpa a imagem caso exista alguma
        string filename;
        input >> filename;                                              //recebe input ao filename
        image = loadFromXPM2(filename);                                 //entrega o filename à função loadFromXPM2
    }

    void Script::xpm2_save(){    //implementação da função xpm2_save()
        string filename;
        input >> filename;                                              //recebe input ao filename
        saveToXPM2(filename, image);                                    //entrega o filename e a imagem à função saveToXPM2 
    }
}
