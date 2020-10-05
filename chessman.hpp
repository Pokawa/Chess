//
// Created by pokawa on 19.09.2020.
//

#ifndef CHESS_CHESSMAN_HPP
#define CHESS_CHESSMAN_HPP

#include "drawable.hpp"
#include "model.hpp"
#include "lib/shaderprogram.h"
#include <iostream>

class Chessman : public Drawable {
public:
    enum class Type {KING = 0, QUEEN, ROOK, KNIGHT, BISHOP, PAWN};
    enum class Color {BLACK = 0, WHITE};

protected:
    int row;
    int column;
    int destinationRow;
    int destinationColumn;
    double animationTimeSpan;
    double animationElapsed;
    double distance;
    bool animationSkipped;

    Chessman::Color color;

public:
    bool visible;

    Chessman(Model* modelData, GLuint textureID, Chessman::Color color) : Drawable(modelData, textureID),
    color(color), visible(true){}

    void setPosition(unsigned int row, unsigned int column) {
        this->row = this->destinationRow = row;
        this->column = this->destinationColumn = column;
        if (this->row == 0 or this->column == 0)
            this->visible = false;
        else
            this->visible = true;
    }

    void move(unsigned int row, unsigned int column) {
        this->destinationRow = row;
        this->destinationColumn = column;

        if (this->willBeVisible())
            this->visible = true;

        if (this->isMoving())
            this->setAnimation();
    }

    void moveInstantly(unsigned int row, unsigned int column) {
        this->setPosition(row, column);
    }

    bool isMoving() {
        return this->row != this->destinationRow or this->column != this->destinationColumn;
    }

    bool willBeVisible() {
        return (this->row == 0 or this->column == 0) and this->destinationColumn != 0 and this->destinationRow != 0;
    }

    void skipAnimation() {
        endAnimation();
    }

    void updateAnimation(double elapseTime) {
        if (this->isMoving()) {
            this->animationElapsed += elapseTime;
            if (this->animationElapsed >= this->animationTimeSpan) {
                endAnimation();
            }
        }
    }

private:
    void endAnimation() {
        this->animationSkipped = false;
        this->row = this->destinationRow;
        this->column = this->destinationColumn;

        if (this->row == 0 or this->column == 0)
            this->visible = false;
        else
            this->visible = true;

        if (this->modelChanged) {
            this->modelData = this->newModel;
            this->modelChanged = false;
        }
    }

    void setAnimation() {
        this->animationElapsed = 0;
        this->distance = std::sqrt(std::pow(this->destinationColumn - this->column, 2) + std::pow(this->destinationRow - this->row, 2));
        this->animationTimeSpan = 0.15 + 0.05 * this->distance;

    }

    float animationElapsedRatio(){
        return this->animationElapsed / this->animationTimeSpan;
    }

    virtual void computeMatrix() {
        glm::mat4 M = glm::mat4(1.0f);

        //Placing on the right square
        auto translateXZPosition = [](auto pos){ return (pos - 1) * 12.5f + 6.25f - 50.0f ;};
        float translateX = translateXZPosition(this->row);
        float translateZ = translateXZPosition(this->column);
        auto currentLocation = glm::vec3(translateX, 0, translateZ);
        M = glm::translate(M, currentLocation);

        if (this->isMoving()) {
            float translateDestinationX = translateXZPosition(this->destinationRow);
            float translateDestinationZ = translateXZPosition(this->destinationColumn);
            auto destinationLocation = glm::vec3(translateDestinationX, 0, translateDestinationZ);

            auto direction = destinationLocation - currentLocation;
            auto animatedLocation = direction * this->animationElapsedRatio();

            animatedLocation.y = std::min(std::pow(20, this->distance), 100.0)  * -this->animationElapsed * (this->animationElapsed - this->animationTimeSpan);

            M = glm::translate(M, animatedLocation);
        }

        M = glm::scale(M, glm::vec3(0.6f, 0.6f, 0.6f));

        if (this->color == Color::WHITE)
            M = glm::rotate(M, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        this->matrix = M;
    }
};

#endif //CHESS_CHESSMAN_HPP
