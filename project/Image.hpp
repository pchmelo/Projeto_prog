#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"
#include <vector>
#include <iostream>

namespace prog
{
  class Image
  {
  private:
    int width_;
    int height_;
    std::vector <std::vector <Color>> img;     //matriz com altura height_ e largura width_ formada por elementos do tipo Color

  public:
    Image(int w, int h, const Color &fill = {255, 255, 255});    //construtor da Image que preenche com uma cor, sendo o branco a cor por omissão
    Image(const Image& old_img);    //copy constructor
    ~Image();              //destructor não é usado
                                                 
    int width() const;     //acessor da variável private width_
    int height() const;    //acessor da variável private height_ 

    Color &at(int x, int y);       //acessor mutável do Color de coordenada x(width_) e y(height_)
    const Color &at(int x, int y) const;   //acessor do Color de coordenada x(width_) e y(height_)
  };
}
#endif
