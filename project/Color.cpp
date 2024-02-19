#include "Color.hpp"

namespace prog {

    Color::Color() {    //Implementação do construtor default com o código rgb da cor preto (0, 0, 0)
        red_ = 0;
        green_ = 0;
        blue_ = 0;

    }

    Color::Color(const Color& other) {    //Implementação do Copy Constructor
        red_ = other.red();
        green_ = other.green();
        blue_ = other.blue();

    }

    Color::Color(rgb_value red, rgb_value green, rgb_value blue) {   //Implementação do construtor com argumentos
        red_ = red;
        green_ = green;
        blue_ = blue;

    }

    rgb_value Color::red() const {   //Implementação dos acessores
        return red_;

    }
    rgb_value Color::green() const {
        return green_;

    }
    rgb_value Color::blue() const {
        return blue_;

    }
 

    rgb_value& Color::red()  {    //Implementação dos acessores mutáveis
        return red_;

    }
    rgb_value& Color::green()  {
      return green_;

    }
    rgb_value& Color::blue()  {
      return blue_;

    }

    bool Color::compare_color(Color cor) const{    //implementação da função compare_color()

        if ((red_ == cor.red()) && (green_ == cor.green()) && (blue_ == cor.blue())){
            return true;
        }
        return false;
    }

    bool Color::operator<(const Color& c) const{ //implementação do operador "menor"
        if(red_ < c.red()){
            return true;
        }
        else if(red_ == c.red()){
            if (green_ < c.green()){
                return true;
            }
            else if(green_ == c.green()){
                if(blue_ < c.blue()){
                    return true;
                }
            }
        }
        return false;
    }

    bool Color::operator>(const Color& c) const{ //implementação do operador "maior"
        if(red_ < c.red()){
            return false;
        }
        else if(red_ == c.red()){
            if (green_ < c.green()){
                return false;
            }
            else if(green_ == c.green()){
                if(blue_ < c.blue()){
                    return false;
                }
            }
        }
        return true;
    }
}
