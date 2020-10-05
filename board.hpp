#ifndef BOARD_HPP_INCLUDED
#define BOARD_HPP_INCLUDED


#include "model.hpp"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include "drawable.hpp"
#include "model.hpp"
#include "texture.hpp"

class Board{
private:
    Drawable boardTop;
    Drawable boardSides;

    Model topModel;
    Model sidesModel;

public:
    Board() : topModel("models/boardtop.obj"),
              sidesModel("models/boardsides.obj"),
              boardTop(&topModel, readTexture("models/textures/chessboard.png")),
              boardSides(&sidesModel, readTexture("models/textures/wood.png")) {}

    void update(ShaderProgram * shader){
        boardTop.updateAndDraw(shader);
        boardSides.updateAndDraw(shader);
    }
};

#endif //BOAR_HPP_INCLUDED