//
// Created by pokawa on 20.09.2020.
//

#ifndef CHESS_GAME_HPP
#define CHESS_GAME_HPP

#include "savedGame.hpp"
#include "placement.hpp"
#include <vector>
#include <iostream>

class Game {
     std::vector<Placement> roundPlacements;
     std::vector<Placement>::iterator iterator;

public:
    SavedGame save;
    int rounds;

    Game(std::string filename) {
        this->save = SavedGame::loadFromFile(filename);
        this->roundPlacements.reserve(this->save.moves.size()+1);
        this->roundPlacements.push_back(this->save.startingPlacement);
        this->iterator = this->roundPlacements.begin();
        this->generatePositions();
        this->rounds =  roundPlacements.size();
    }

    int currentRound() {
        return this->iterator - this->roundPlacements.begin() + 1;
    }

    Placement nextPlacement() {
        if (this->iterator + 1 < this->roundPlacements.end())
            return *(++this->iterator);
        else
            return *this->iterator;
    }

    Placement previousPlacement() {
        if (this->iterator - 1 >= this->roundPlacements.begin())
            return *(--this->iterator);
        else
            return *this->iterator;
    }

    Placement getPlacement(uint index) {
        this->iterator = this->roundPlacements.begin() + index;
        return *this->iterator;
    }

private:
    void generatePositions() {
        for (auto & move : this->save.moves) {
            this->roundPlacements.push_back(this->roundPlacements.back().makeMove(move));
        }
    }

};

#endif //CHESS_GAME_HPP
