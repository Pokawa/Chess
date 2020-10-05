//
// Created by pokawa on 19.09.2020.
//

#ifndef CHESS_DRAWABLE_HPP
#define CHESS_DRAWABLE_HPP

#include "model.hpp"

class Drawable {
protected:
    Model * modelData;
    Model * newModel;
    bool modelChanged;
    GLuint texture;
    glm::mat4 matrix;

public:
    Drawable(Model * modelData, GLuint texture) : modelData(modelData), newModel(modelData), texture(texture), modelChanged(false){}

    void draw(ShaderProgram* shader, glm::mat4 matrix) {
        this->matrix = matrix;
        draw(shader);
    }

    void draw(ShaderProgram* shader) {
        this->applyMatrix(shader);
        this->enableVertexAttribArray(shader);
        this->passVertexArrays(shader);
        this->drawArrays(shader);
        this->disableVertexAttribArray(shader);
    }

    void changeModel(Model * model) {
        this->newModel = model;
        this->modelChanged = true;
    }

    void updateAndDraw(ShaderProgram* shader) {
        computeMatrix();
        draw(shader);
    }

protected:
    virtual void computeMatrix() {
        this->matrix = glm::mat4(1.0f);
    };

    virtual void drawArrays(ShaderProgram* shader) {
        glUniform1i(shader->u("textureMap"),0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->texture);
        glDrawArrays(GL_TRIANGLES, 0, this->modelData->vertexCount);
    }

private:
    void applyMatrix(ShaderProgram* shader) {
        glUniformMatrix4fv(shader->u("M"), 1, false, glm::value_ptr(this->matrix));
    }

    void enableVertexAttribArray(ShaderProgram* shader) {
        glEnableVertexAttribArray(shader->a("vertex"));
        glEnableVertexAttribArray(shader->a("normal"));
        glEnableVertexAttribArray(shader->a("texCoord"));
    }

    void disableVertexAttribArray(ShaderProgram* shader) {
        glDisableVertexAttribArray(shader->a("vertex"));
        glDisableVertexAttribArray(shader->a("normal"));
        glDisableVertexAttribArray(shader->a("texCoord"));
    }

    void passVertexArrays(ShaderProgram* shader) {
        glVertexAttribPointer(shader->a("vertex"), 4, GL_FLOAT, false, 0, this->modelData->coordinates.data());
        glVertexAttribPointer(shader->a("normal"), 4, GL_FLOAT, false, 0, this->modelData->normalVectors.data());
        glVertexAttribPointer(shader->a("texCoord"),2,GL_FLOAT,false,0, this->modelData->textureCoordinates.data());
    }
};

#endif //CHESS_DRAWABLE_HPP
