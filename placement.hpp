#ifndef PLACEMENT_HPP_INCLUDED
#define PLACEMENT_HPP_INCLUDED

#include <array>
#include "move.hpp"

bool contains(const std::string & a, const std::string & b) {
    return a.find(b) != std::string::npos;
}

class Placement {
public:
    std::array<uint, 32> row;
    std::array<uint, 32> column;
    bool promotion;
    unsigned int promotionIndex;
    unsigned int promotionModelId;



    int findOn(uint row, uint column) {
        for (int i = 0; i < 32; ++i) {
            if (this->row[i] == row and this->column[i] == column)
                return i;
        }
        return -1;
    }

    void moveTo(uint index, uint row, uint column) {

        this->row[index] = row;
        this->column[index] = column;
    }

    Placement makeMove(Move move) {
        Placement next = *this;
        next.promotion = false;

        if (contains(move.action, "t")) {
            auto index = next.findOn(move.toRow, move.toColumn);
            if (index >= 0)
                next.moveTo(index, 4, 0);
        }
        if (contains(move.action, "e")) {
            auto opponentRow = move.toRow + (move.player == Move::Color::BLACK ? 1 : -1);
            auto index = next.findOn(opponentRow, move.toColumn);
            if (index >= 0)
                next.moveTo(index, 4, 0);
        }
        if (contains(move.action, "l")) {
            if (move.player == Move::Color::BLACK) {
                auto rookIndex = next.findOn(8, 1);
                if (rookIndex == 18 or rookIndex == 19) {
                    next.moveTo(rookIndex, 8, 4);
                }
            } else {
                auto rookIndex = next.findOn(1, 1);
                if (rookIndex == 2 or rookIndex == 3) {
                    next.moveTo(rookIndex, 1, 4);
                }
            }
        }
        if (contains(move.action, "s")) {
            if (move.player == Move::Color::BLACK) {
                auto rookIndex = next.findOn(8, 8);
                if (rookIndex == 18 or rookIndex == 19) {
                    next.moveTo(rookIndex, 8, 6);
                }
            } else {
                auto rookIndex = next.findOn(1, 8);
                if (rookIndex == 2 or rookIndex == 3) {
                    next.moveTo(rookIndex, 1, 6);
                }
            }
        }

        if (contains(move.action, "p")) {
            next.promotion = true;
            next.promotionIndex = next.findOn(move.fromRow, move.fromColumn);
            this->promotion = true;
            this->promotionModelId = 5;
            this->promotionIndex = next.findOn(move.fromRow, move.fromColumn);

            if (contains(move.action, "q")) {
                next.promotionModelId = 1;
            }
            if (contains(move.action, "r")) {
                next.promotionModelId = 2;
            }
            if (contains(move.action, "k")) {
                next.promotionModelId = 3;
            }
            if (contains(move.action, "b")) {
                next.promotionModelId = 4;
            }
        }

        if (contains(move.action, "w")) {
            for (int i = 0; i < 32; ++i) {
                next.moveTo(i, 4, 0);
            }

            next.moveTo(move.player == Move::Color::WHITE ? 0 : 16, move.player == Move::Color::WHITE ? 4 : 5, 5 );
        }

        if (contains(move.action, "d")) {
            for (int i = 0; i < 32; ++i) {
                next.moveTo(i, 4, 0);
            }

            next.moveTo(0, 4, 5);
            next.moveTo(16,5,5);
        }

        auto index = next.findOn(move.fromRow, move.fromColumn);
        if (index >= 0)
            next.moveTo(index, move.toRow, move.toColumn);

        return next;
    }
};


Placement defaultPlacement{
    {1, 1, 1, 1, 1, 1, 1, 1,
     2, 2, 2, 2, 2, 2, 2, 2,
     8, 8, 8, 8, 8, 8, 8, 8,
     7,7,7,7,7,7,7,7},
    {5, 4, 1, 8, 2, 7, 3, 6,
    1,2,3,4,5,6,7,8,
    5, 4, 1, 8, 2, 7, 3, 6,
    1,2,3,4,5,6,7,8}};

#endif //PLACEMENT_HPP_INCLUDED