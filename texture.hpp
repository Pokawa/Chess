//
// Created by pokawa on 20.09.2020.
//

#ifndef CHESS_TEXTURE_HPP
#define CHESS_TEXTURE_HPP

#include "lib/lodepng.h"
#include <exception>

class InvalidTextureFile : std::exception {};

GLuint readTexture(const std::string & filename)
{
    GLuint tex;
    glActiveTexture(GL_TEXTURE0);
    //Wczytanie do pamięci komputera
    std::vector<unsigned char> image; //Alokuj wektor do wczytania obrazka
    unsigned width, height;			  //Zmienne do których wczytamy wymiary obrazka
    //Wczytaj obrazek
    unsigned error = lodepng::decode(image, width, height, filename);

    if (error)
        throw InvalidTextureFile();

    //Import do pamięci karty graficznej
    glGenTextures(1, &tex);			   //Zainicjuj jeden uchwyt
    glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
    //Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char *)image.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return tex;
}

#endif //CHESS_TEXTURE_HPP
