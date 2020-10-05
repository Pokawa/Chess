//
// Created by pokawa on 20.09.2020.
//

#ifndef CHESS_CHESSGAME_HPP
#define CHESS_CHESSGAME_HPP

#include "placement.hpp"
#include <vector>
#include <fstream>
#include <exception>
#include "move.hpp"

class SavedGame {
    class InvalidFile : std::exception {};
public:
    Placement startingPlacement;
    std::string playerWhite;
    std::string playerBlack;
    std::vector<Move> moves;

    static SavedGame loadFromFile(const std::string & filename) {
        SavedGame game;
        std::ifstream file(filename);

        if (!file.is_open()){
            throw SavedGame::InvalidFile();
        }

        getline(file, game.playerWhite);
        getline(file, game.playerBlack);

        for (int i = 0; i < 32; ++i) {
            char column;
            unsigned int row;
            file >> column >> row;
            game.startingPlacement.column[i] = translateColumn(column);
            game.startingPlacement.row[i] = row;
        }

        while(!file.eof()) {
            char fromColumn, toColumn;
            unsigned int fromRow, toRow;
            char color;
            std::string action;

            file >> color >> fromColumn >> fromRow >> action >> toColumn >> toRow;
            auto p = translateColor(color);
            Move move = {translateColumn(fromColumn), fromRow, translateColumn(toColumn), toRow, action, p};
            game.moves.push_back(move);
        }
        game.moves.shrink_to_fit();
        return game;
    }

private:
    static unsigned int translateColumn(char character) {
        if (character == 'o') return 0;
        return character - 'a' + 1;
    }

    static Move::Color translateColor(char character) {
        return character == 'b' ? Move::Color::BLACK : Move::Color::WHITE;
    }
};

#endif //CHESS_CHESSGAME_HPP
