//
// Created by pokawa on 20.09.2020.
//

#ifndef CHESS_CHESSPIECES_HPP
#define CHESS_CHESSPIECES_HPP

#include "chessman.hpp"
#include <vector>
#include <memory>
#include <array>
#include "placement.hpp"
#include "texture.hpp"

class ChessPieces {
private:
    std::vector<Chessman> chessmen;
    std::array<Model, 6> models;
    GLuint lightTexture;
    GLuint darkTexture;

public:
    ChessPieces() {
        this->loadModels();
        this->loadTextures();
        this->constructChessmen();
    }

    bool isMoving() {
        for (auto & piece : chessmen) {
            if (piece.isMoving())
                return true;
        }
        return false;
    }

    void update(ShaderProgram* shader, double elapsedTime) {
        for (auto & piece : this->chessmen) {
            if (piece.visible) {
                piece.updateAnimation(elapsedTime);
                piece.updateAndDraw(shader);
            }
        }
    }

    void placeChessmen(Placement startingPlacement) {
        for (int i = 0; i < 32; ++i) {
            this->chessmen[i].setPosition(startingPlacement.row[i], startingPlacement.column[i]);
        }
    }

    void updatePlacement(Placement newPlacement) {
        for (int i = 0; i < 32; ++i) {
            this->chessmen[i].move(newPlacement.row[i], newPlacement.column[i]);

            if (newPlacement.promotion){
                this->chessmen[newPlacement.promotionIndex].changeModel(&this->models[newPlacement.promotionModelId]);
            }
        }
    }

    void updatePlacementInstantly(Placement newPlacement) {
        for (int i = 0; i < 32; ++i) {
            this->chessmen[i].moveInstantly(newPlacement.row[i], newPlacement.column[i]);

            if (newPlacement.promotion){
                this->chessmen[newPlacement.promotionIndex].changeModel(&this->models[newPlacement.promotionModelId]);
            }
        }
    }

    void skipAnimation() {
        for (auto & piece : this->chessmen) {
            piece.skipAnimation();
        }
    }

private:
    void constructChessmen() {
        this->chessmen.reserve(32);

        this->chessmen.emplace_back(&models[0], lightTexture, Chessman::Color::WHITE);
        this->chessmen.emplace_back(&models[1], lightTexture, Chessman::Color::WHITE);
        this->chessmen.emplace_back(&models[2], lightTexture, Chessman::Color::WHITE);
        this->chessmen.emplace_back(&models[2], lightTexture, Chessman::Color::WHITE);
        this->chessmen.emplace_back(&models[3], lightTexture, Chessman::Color::WHITE);
        this->chessmen.emplace_back(&models[3], lightTexture, Chessman::Color::WHITE);
        this->chessmen.emplace_back(&models[4], lightTexture, Chessman::Color::WHITE);
        this->chessmen.emplace_back(&models[4], lightTexture, Chessman::Color::WHITE);
        this->chessmen.emplace_back(&models[5], lightTexture, Chessman::Color::WHITE);
        this->chessmen.emplace_back(&models[5], lightTexture, Chessman::Color::WHITE);
        this->chessmen.emplace_back(&models[5], lightTexture, Chessman::Color::WHITE);
        this->chessmen.emplace_back(&models[5], lightTexture, Chessman::Color::WHITE);
        this->chessmen.emplace_back(&models[5], lightTexture, Chessman::Color::WHITE);
        this->chessmen.emplace_back(&models[5], lightTexture, Chessman::Color::WHITE);
        this->chessmen.emplace_back(&models[5], lightTexture, Chessman::Color::WHITE);
        this->chessmen.emplace_back(&models[5], lightTexture, Chessman::Color::WHITE);

        this->chessmen.emplace_back(&models[0], darkTexture, Chessman::Color::BLACK);
        this->chessmen.emplace_back(&models[1], darkTexture, Chessman::Color::BLACK);
        this->chessmen.emplace_back(&models[2], darkTexture, Chessman::Color::BLACK);
        this->chessmen.emplace_back(&models[2], darkTexture, Chessman::Color::BLACK);
        this->chessmen.emplace_back(&models[3], darkTexture, Chessman::Color::BLACK);
        this->chessmen.emplace_back(&models[3], darkTexture, Chessman::Color::BLACK);
        this->chessmen.emplace_back(&models[4], darkTexture, Chessman::Color::BLACK);
        this->chessmen.emplace_back(&models[4], darkTexture, Chessman::Color::BLACK);
        this->chessmen.emplace_back(&models[5], darkTexture, Chessman::Color::BLACK);
        this->chessmen.emplace_back(&models[5], darkTexture, Chessman::Color::BLACK);
        this->chessmen.emplace_back(&models[5], darkTexture, Chessman::Color::BLACK);
        this->chessmen.emplace_back(&models[5], darkTexture, Chessman::Color::BLACK);
        this->chessmen.emplace_back(&models[5], darkTexture, Chessman::Color::BLACK);
        this->chessmen.emplace_back(&models[5], darkTexture, Chessman::Color::BLACK);
        this->chessmen.emplace_back(&models[5], darkTexture, Chessman::Color::BLACK);
        this->chessmen.emplace_back(&models[5], darkTexture, Chessman::Color::BLACK);
    }

    void loadModels() {
        models[0] = Model("models/king.obj");
        models[1] = Model("models/queen.obj");
        models[2] = Model("models/rook.obj");
        models[3] = Model("models/knight.obj");
        models[4] = Model("models/bishop.obj");
        models[5] = Model("models/pawn.obj");
    }

    void loadTextures() {
        lightTexture = readTexture("models/textures/lightwood.png");
        darkTexture = readTexture("models/textures/darkwood.png");
    }
};

#endif //CHESS_CHESSPIECES_HPP
