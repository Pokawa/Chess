#ifndef MOVE_HPP_INCLUDED
#define MOVE_HPP_INCLUDED

#include <utility>



struct Move {
    enum class Color {WHITE, BLACK};
    unsigned int fromColumn, fromRow;
    unsigned int toColumn, toRow;
    std::string action;
    Color player;
};

#endif //MOVE_HPP_INCLUDED