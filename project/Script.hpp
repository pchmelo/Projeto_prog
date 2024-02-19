#ifndef __prog_Script_hpp__
#define __prog_Script_hpp__

#include <string>
#include <fstream>
#include "Image.hpp"

namespace prog
{
  class Script
  {
  public: 
    Script(const std::string &filename);
    ~Script();
    void run();
  private:
    // Current image.
    Image *image;
    // Input stream for reading script commands.
    std::ifstream input;
  private:
    // Private functions
    void clear_image_if_any();
    void open();
    void blank();
    void save();

    //Sumário: Todas as funcionalidades foram implementadas

    void to_gray_scale();    //função que transforma a cor de cada pixel da imagem de (r,g,b) para (v,v,v), sendo v = (r+g+b)/3

    void crop();    //função que recebe as coordenadas de um ponto (x,y) que representa o canto superior esquerdo de um retângulo de w de width_ e h de height_ e corta a imagem toda, à exceção desse retângulo

    void invert();    //função que transforma a cor de cada pixel da imagem de (r,g,b) para (255-r,255-g,255-b)

    void replace();    //função que troca a cor todos os pixeis (r1,g1,b1) para a cor (r2,g2,b2)

    void fill();    //função que preenche o retângulo cujo canto superior esquerdo tem coordenadas (x,y) e h de height_ e w de width_ com a cor (r,g,b)

    void h_mirror();    //função que espelha a imagem na horizontal

    void v_mirror();    //função que espelha a imagem na vertical

    void add();    //função que adiciona a imagem contida em filename, com canto superior esquerdo na posição (x,y) à exceção da cor (r,g,b)

    void rotate_left();    //função que rotaciona a imagem 90º para a esquerda

    void rotate_right();    //função que rotaciona a imagem 90º para a direita

    void median_filter();    //função que calcula e atribui a um pixel a mediana das cores dos pixeis à volta dele numa window de tamanho ws 

    void xpm2_open();    //função que transforma um ficheiro .xpm em imagem

    void xpm2_save();    //função que transforma imagem em ficheiro .xpm
  };
}
#endif
