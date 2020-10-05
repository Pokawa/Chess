//
// Created by pokawa on 21.09.2020.
//

#ifndef CHESS_APP_HPP
#define CHESS_APP_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include "lib/lodepng.h"
#include "lib/shaderprogram.h"
#include "chess.hpp"

float aspectRatio = 4. / 3.;
double previousPosX = -1;
double previousPosY = -1;
double angleThetha = glm::radians(90.0);
double anglePhi = glm::radians(15.0);
GLFWwindow *window;
std::unique_ptr <Chess> chess;
std::unique_ptr <ShaderProgram> shader;

void error_callback(int error, const char *description) {
    fputs(description, stderr);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_RIGHT) {
            chess->nextRound();
            glfwSetWindowTitle(window, chess->getTitle().c_str());
        }
        if (key == GLFW_KEY_LEFT) {
            chess->previousRound();
            glfwSetWindowTitle(window, chess->getTitle().c_str());
        }
    }
}

void mouseCursosCallback(GLFWwindow *window, double xpos, double ypos) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (previousPosX == -1 or previousPosY == -1) {
            previousPosX = xpos;
            previousPosY = ypos;
        }

        angleThetha += (xpos - previousPosX) / 200;
        anglePhi = glm::clamp(anglePhi + (ypos - previousPosY) / 200, glm::radians(15.0),
                              glm::radians(89.0));

        previousPosX = xpos;
        previousPosY = ypos;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        previousPosX = -1;
        previousPosY = -1;
    }

}

void dropCallback(GLFWwindow *window, int count, const char **paths) {
    if (count == 1) {
        std::string filename{paths[0]};
        chess->loadGame(filename);
        glfwSetWindowTitle(window, chess->getTitle().c_str());
    }
}

void windowResizeCallback(GLFWwindow *window, int width, int height) {
    if (height == 0)
        return;
    aspectRatio = (float) width / (float) height;
    glViewport(0, 0, width, height);
}

void initOpenGLProgram() {
    glClearColor(0.8, 0.8, 0.8, 1);
    glEnable(GL_DEPTH_TEST);
    glfwSetWindowSizeCallback(window, windowResizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetDropCallback(window, dropCallback);
    glfwSetCursorPosCallback(window, mouseCursosCallback);

    chess = std::make_unique<Chess>();
    shader = std::make_unique<ShaderProgram>("shaders/v_simplest.glsl", nullptr, "shaders/f_simplest.glsl");
}

void initialize() {
    glfwSetErrorCallback(error_callback); //Zarejestruj procedurę obsługi błędów

    if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
        fprintf(stderr, "Nie można zainicjować GLFW.\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(1000, 750, "Chess", NULL,
                              NULL); //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

    if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
    {
        fprintf(stderr, "Nie można utworzyć okna.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
    glfwSwapInterval(1);            //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

    if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
        fprintf(stderr, "Nie można zainicjować GLEW.\n");
        exit(EXIT_FAILURE);
    }

    initOpenGLProgram();
}

void drawScene(double time) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double t = 150 * glm::cos(anglePhi);
    double y = 150 * glm::sin(anglePhi);
    double x = t * glm::cos(angleThetha);
    double z = t * glm::sin(angleThetha);

    glm::mat4 V = glm::lookAt(
            glm::vec3(x, y, z),
            glm::vec3(0, 0, 0),
            glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 P = glm::perspective((float)glm::radians(50.0), aspectRatio, 0.01f, 300.0f);

    shader->use();
    glUniformMatrix4fv(shader->u("P"), 1, false, glm::value_ptr(P));
    glUniformMatrix4fv(shader->u("V"), 1, false, glm::value_ptr(V));
    chess->update(shader.get(), time);
    glfwSwapBuffers(window);
}

void run() {
    glfwSetTime(0);
    while (!glfwWindowShouldClose(window)) {
        auto time = glfwGetTime();
        glfwSetTime(0);
        drawScene(time);
        glfwPollEvents();
    }
}

void end() {
    glfwDestroyWindow(window);
    glfwTerminate();
}


#endif //CHESS_APP_HPP
