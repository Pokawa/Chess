//
// Created by pokawa on 20.09.2020.
//

#ifndef CHESS_CHESS_HPP
#define CHESS_CHESS_HPP

#include "game.hpp"
#include "placement.hpp"
#include "chessPieces.hpp"
#include "board.hpp"
#include <memory>
#include <algorithm>
#include "lib/shaderprogram.h"

class Chess {
    Board board;
    ChessPieces chessmen;
    std::unique_ptr<Game> game;

public:
    Chess() {
        this->chessmen.placeChessmen(defaultPlacement);
    }

    void loadGame(const std::string & filename) {
        this->game = std::make_unique<Game>(filename);
        this->chessmen.placeChessmen(this->game->save.startingPlacement);
        std::cout << "loaded " << filename << " rounds: " << this->game->save.moves.size() << std::endl;
    }

    bool isGameLoaded() {
        return this->game != nullptr;
    }

    std::string getTitle() {
        return this->game->save.playerWhite + " vs " + this->game->save.playerBlack + " " + std::to_string(this->game->currentRound()) + "/" + std::to_string(this->game->rounds) + " rounds";
    }

    void nextRound() {
        if(this->isGameLoaded()) {
            this->chessmen.skipAnimation();
            if (!this->chessmen.isMoving()) {
                this->chessmen.updatePlacement(this->game->nextPlacement());
            }
        }
    }

    void previousRound() {
        if(this->isGameLoaded()) {
            this->chessmen.skipAnimation();
            if (!this->chessmen.isMoving()) {
                this->chessmen.updatePlacement(this->game->previousPlacement());
            }
        }
    }

    void update(ShaderProgram* shader, double elapsedTime) {
        this->chessmen.update(shader, elapsedTime);
        this->board.update(shader);
    }
};

#endif //CHESS_CHESS_HPP
