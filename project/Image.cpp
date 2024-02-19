#include "Image.hpp"
#include "Color.hpp"
#include <vector>

namespace prog
{
  Image::Image(int w, int h, const Color &fill){    //implementação do construtor da Image
      std::vector <Color> t;

      width_ = w;
      height_ = h;

      for(int i = 0; i < h; i++){        //for loop que cria um vetor com tamanho height_ que é preenchido por vetores t
        for (int j = 0; j < w; j++){     //for loop que cria um vetor t com tamanho width_ que é preenchido pela cor fill
            t.push_back(fill);

        }
        img.push_back(t);
        t.clear();    //método para apagar o vetor t

      } 
  }

  Image::Image(const Image& old_img){    //implementação do copy construtor
    std::vector <Color> t;
    
    width_ = old_img.width();
    height_ = old_img.height();

    for (int i = 0; i < height_; i++){    //for loop que cria um vetor com tamanho height_ que é preenchido por vetores t 
      for (int j = 0; j < width_; j++){    //for loop que cria um vetor t com tamanho width_ que é preenchido pelos pixeis da imagem a copiar
        t.push_back(old_img.at(j,i));
      }
      img.push_back(t);
      t.clear();    //método para apagar o vetor t
    }
  }

  Image::~Image(){
    //destructor não é usado
  }

  int Image::width() const{    //implementação dos acessores
    return width_;

  }

  int Image::height() const{
    return height_;

  }

  Color& Image::at(int x, int y){    //implementação dos acessores mutável e não mutável de cor
    return img[y][x];    //as coordenadas precisam de ser colocadas ao contrário pois o x representa a width e o y representa a height

  }

  const Color& Image::at(int x, int y) const{
    return img[y][x];

  }
}
