//
// Created by pokawa on 19.09.2020.
//

#ifndef CHESS_MODEL_HPP
#define CHESS_MODEL_HPP

#include <string>
#include <glm/glm.hpp>
#include <exception>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>

class Model {
public:
    std::vector<float> coordinates;
    std::vector<float> textureCoordinates;
    std::vector<float> normalVectors;
    int vertexCount;

    Model(std::string filename) {
        loadOBJ(filename);
    }

    Model() {}

    class InvalidModelFile : std::exception {};
private:


    void loadOBJ(std::string filename)
    {
        std::ifstream objFile(filename);
        std::vector<glm::fvec3> positions, normals;
        std::vector<glm::fvec2> textures;
        this->vertexCount = 0;

        if (!objFile.is_open())
        {
            throw Model::InvalidModelFile();
        }

        while (!objFile.eof())
        {
            std::string prefix;
            objFile >> prefix;

            if (prefix == "v") //Vertex position
            {
                glm::fvec3 temp;
                objFile >> temp.x >> temp.y >> temp.z;
                positions.push_back(temp);
            }
            else if (prefix == "vt") //Texture coordinates
            {
                glm::fvec2 temp;
                objFile >> temp.x >> temp.y;
                textures.push_back(temp);
            }
            else if (prefix == "vn") //Normal vectors
            {
                glm::fvec3 temp;
                objFile >> temp.x >> temp.y >> temp.z;
                normals.push_back(temp);
            }
            else if(prefix=="f") //Triangle faces
            {
                this->vertexCount += 3;
                for (int i = 0; i < 3; ++i) {
                    int positionIndex, textureIndex, normalIndex;
                    char spacer;

                    objFile >> positionIndex >> spacer >> textureIndex >> spacer >> normalIndex;

                    auto vertexPosition = {positions[positionIndex - 1].x, positions[positionIndex - 1].y, positions[positionIndex - 1].z, 1.f};
                    auto texturePosition = {textures[textureIndex - 1].x, textures[textureIndex - 1].y};
                    auto normalPosition = {normals[normalIndex - 1].x, normals[normalIndex - 1].y, normals[normalIndex - 1].z, 0.f};

                    this->coordinates.insert(coordinates.end(), vertexPosition);
                    this->textureCoordinates.insert(textureCoordinates.end(), texturePosition);
                    this->normalVectors.insert(normalVectors.end(), normalPosition);
                }
            } else {
                getline(objFile, prefix);
            }
        }
        this->coordinates.shrink_to_fit();
        this->textureCoordinates.shrink_to_fit();
        this->normalVectors.shrink_to_fit();

    }
};

#endif //CHESS_MODEL_HPP
