#include "XPM2.hpp"
#include "Script.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>


namespace prog {
    Color hex_to_color (const std::string hex_value){    //implementação da função hex_to_color
        Color cor;
        std::map <char,int> hex_convert = {{'0', 0}, {'1', 1}, {'2', 2}, {'3', 3},                              //
                                            {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7},                             //
                                            {'8', 8}, {'9', 9}, {'A', 10}, {'B', 11},                           //map que associa caracteres aos seus respectivos valores decimais
                                            {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15},{'a', 10}, {'b', 11},    //
                                            {'c', 12}, {'d', 13}, {'e', 14}, {'f', 15}};                        //

        cor.red() = hex_convert[hex_value[1]] * 16 + hex_convert[hex_value[2]];             //
        cor.green() = hex_convert[hex_value[3]] * 16 + hex_convert[hex_value[4]];           //atribuição dos valores rgb convertidos a partir de hexadecimal usando o map à variável cor
        cor.blue() = hex_convert[hex_value[5]] * 16 + hex_convert[hex_value[6]];            //

        return cor;
    }

    Image* loadFromXPM2(const std::string& file) {    //implementação da função loadFromXPM2
        int w = 0, h = 0, n_colors, n_chars, line_num = 1, line_num_img = 0;
        Image* image;
        
        char character;

        std::map <char,Color> legenda;
        std::string word, color_hex, line;
        std::ifstream xpm2_file (file);
        
        while (getline (xpm2_file, line)){           //while loop que lê o ficheiro .xpm linha a linha
            std::istringstream line_chr (line);
            if (line_num == 1){                      //ignora o conteúdo na linha 1
                
            }

            else if (line_num == 2){                 //caso o número da linha seja 2, lê as informações sobre a imagem
                line_chr >> w;  
                line_chr >> h;
                line_chr >> n_colors;
                line_chr >> n_chars;

                image = new Image(w, h);            //cria uma nova imagem com as informações que foram obtidas na leitura anterior
            }
            else if (line_num >= 3 && line_num < 3 + n_colors){ //lê a informação fornecida sobre as cores entre a linha 3 e a linha 3 + n_colors 
                line_chr >> character;
                line_chr >> word;
                line_chr >> word;
            
                legenda.insert({character, hex_to_color(word)}); //adiciona um par à legenda que associa um caracter a uma cor
            }

            else {
                for (int i = 0; i < w; i++){        //for loop que percorre a linha de caracteres que representa a imagem
                        line_chr >> character;
                        image->at(i, line_num_img) = legenda[character];    //adiciona à imagem no pixel (i, line_num_img) a cor da legenda correspondente ao caracter lido 
                }
                line_num_img++;
            }
            line_num ++;
        }

        return image;
    }

    std::string color_to_hex (const Color cor){        //implementação da função color_to_hex
        rgb_value rgb;
        std::vector <rgb_value> cor_values= {cor.red(), cor.green(), cor.blue()};
        std::string res = "#";

        std::map <int,char> hex_convert = {{0, '0'}, {1, '1'}, {2, '2'}, {3, '3'},          //map que associa um número decimal ao seu respectivo caracter hexadecimal
                                            {4, '4'}, {5, '5'}, {6, '6'}, {7, '7'},         //
                                            {8, '8'}, {9, '9'}, {10, 'A'}, {11, 'B'},       //
                                            {12, 'C'}, {13, 'D'}, {14, 'E'}, {15, 'F'}};    //
        
        for (size_t i = 0; i < cor_values.size(); i++){     //for loop que percorre o vector que guarda os valores rgb da variável cor
            rgb = cor_values[i];
 
            if (rgb > 15){                          
                for (int i = 1; i <= 16; i++){      //algoritmo que converte um valor rgb numa string que representa o mesmo valor em hexadecimal
                    if (rgb - i * 16 < 0){
                        res += hex_convert[i-1];    
                        rgb -= ((i - 1) * 16); 
                        res += hex_convert[rgb];   
                        break;
                    }
                }
            }
            else{
                res += '0';
                res += hex_convert[rgb];
            }
        }
        
        return res; 
    }

    void saveToXPM2(const std::string& file, const Image* image) { //implementação da função saveToXPM2
        std::ofstream xpm_file(file);
        int num_cor = 0;
        Color cor;
        char caracter = 33;
        std::string line;

        int w = image->width();
        int h = image->height();

        std::map <Color,char> legenda_1; 
        std::map <char,std::string> legenda_2;

        std::map <Color,char>::iterator it;

        for (int i = 0; i < h; i++){        //for loop que percorre a matriz que representa a imagem
            for (int j = 0; j < w; j++){
                cor = image->at(j, i);
                it = legenda_1.find(cor);

                if(it == legenda_1.end()){      //caso a cor presente no pixel (j,i) ainda não esteja contida na legenda, adicionar essa mesma com o seu caracter correspondente
                    legenda_1[cor] = caracter;
                    legenda_2[caracter] = color_to_hex(cor);    //legenda que guarda o caracter associado à cor na legenda_1 e a cor que este representa numa string hexadecimal

                    caracter += 1;          //acumulador que muda o valor de caracter para o proximo caracter da tabela ASCII
                    num_cor += 1;
                }
                
            }
        }
        
        caracter = 33;

        xpm_file << "! XPM2" << std::endl;      //escreve a primeira linha do ficheiro .xpm
        xpm_file << std::to_string(w) << ' ' << std::to_string(h) << ' ' << std::to_string(num_cor) << ' ' << std::to_string(1) << std::endl; //escreve a segunda linha do ficheiro .xpm, que contém a informação sobre a imagem
        
        for (int i = 0; i < num_cor; i++){      //for loop que escreve as linhas que contéem a informação sobre as cores
            xpm_file << caracter << " c " << legenda_2[caracter] << std::endl;
            caracter += 1;
        }

        for (int i = 0; i < h; i++){        //for loop que escreve as linhas de caracteres que representam a imagem
            for (int j = 0; j < w; j++){
                xpm_file << legenda_1[image->at(j,i)];      //escreve o caracter associado à cor presente no pixel (j,i)
            }
            xpm_file << std::endl;
        }
    }
}
