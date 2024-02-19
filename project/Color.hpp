#ifndef __prog_Color_hpp__
#define __prog_Color_hpp__

namespace prog
{
  typedef unsigned char rgb_value;
  class Color
  {
    private:
      rgb_value red_;
      rgb_value green_; 
      rgb_value blue_;
      //variáveis privadas que representa o código RGB de cada pixel 

    public:
      Color(); //construtor default 
      Color(const Color& c); //copy
      Color(rgb_value r, rgb_value g, rgb_value b); //construtor com argumentos

      rgb_value red() const;   //acessor para o red_ de um pixel
      rgb_value& red();        //acessor mutável para o red_ de um pixel

      rgb_value green() const; //acessor para o green_ de um pixel
      rgb_value& green();      //acessor mutável para o green_ de um pixel

      rgb_value blue() const;  //acessor para o blue_ de um pixel
      rgb_value& blue();       //acessor mutável para o blue_ de um pixel

      bool operator<(const Color& c) const; //operador "menor" de cor
      bool operator>(const Color& c) const; //operador "maior" de cor

      bool compare_color(Color cor) const;  //função que compara duas cores (return true se forem iguais)
  };
}
#endif
