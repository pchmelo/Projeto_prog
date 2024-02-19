#ifndef __prog_XPM2_hpp__
#define __prog_XPM2_hpp__

#include <string>
#include "Image.hpp"
#include <string>
#include <iostream>
#include "Color.hpp"

namespace prog {
    
    Image* loadFromXPM2(const std::string &file);    //função que lê um ficheiro .xpm e cria uma imagem segundo as informações obtidas

    void saveToXPM2(const std::string& file, const Image* img);    //função que lê uma imagem e cria um ficheiro .xpm a partir da informação obtida na leitura

    Color hex_to_color (const std::string hex_value);    //função que transforma uma string de valores hexadecimais em valores do tipo Color

    std::string color_to_hex (const Color cor);    //função que transforma valores do tipo Color em strings de valores hexadecimais 
}
#endif
