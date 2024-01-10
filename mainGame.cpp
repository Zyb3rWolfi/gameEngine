//
// Created by Zyb3rWolfi on 08/01/2024.
//

#include "mainGame.h"
#include<GLEW.h>
#include <SDL.h>
#include<windows.h>
#include<iostream>
#include<string>
#include "sprites.h"

/* Error Management*/
void FatalError(std::string errorString) {
    std::cout << errorString << std::endl;
    std::cout << "Press any key to quit";
    int tmp;
    std::cin >> tmp;
    SDL_Quit();
}

mainGame::mainGame() : _time(0.0f) {

    _window = nullptr;
    _screenWidth = 1920;
    _screenHeight = 1080;
    _gameState = GameState::PLAY;
}

mainGame::~mainGame() {


}

/* Function which runs at the start*/
void mainGame::run() {

    initSystems();
    _sprite.init(-1, -1, 2, 2);
    gameLoop();
}

/* Inits all the needed systems*/
void mainGame::initSystems() {

    // Init SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    /* Creating a window */
    _window = SDL_CreateWindow("SDL Engine",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               _screenWidth,
                               _screenHeight,
                               SDL_WINDOW_OPENGL);

    /* If we have an error*/
    if (_window == nullptr) {
        FatalError("SDL window couldn't be created");
    }

    /* Creates context for debugging*/
    SDL_GLContext glcontext = SDL_GL_CreateContext(_window);

    if (glcontext == nullptr) {
        FatalError("SDL Context could not be created");
    }

    /* We initlize OpenGL and store it in error in case there is one */
    GLenum  error =  glewInit();

    if (error != GLEW_OK) {
        FatalError("Couldn't init glew!");
    }

    /* Setting it to have a buffer of 2*/
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    /* Sets the colours for the background*/
    glClearColor(0.0f, 0.0f, 0.0f, 1.0);
    initShaders();
}

void mainGame::initShaders() {
    // GLSLProgram.cpp
    _colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
    _colorProgram.addAttribute("vertexPosition");
    _colorProgram.addAttribute("vertexColor");
    _colorProgram.linkShaders();

}

/* The main game loop*/
void mainGame::gameLoop() {

    /*If the user has not clicked exit*/
    while (_gameState != GameState::EXIT) {
        _time += 0.01f;
        processInput();
        drawGame();
    }

}
/* this processes all the inputs*/
void mainGame::processInput() {

    /* Creating an event which stores user events*/
    SDL_Event evnt;
    /* if the event does exist we loop through it till it doesn't*/
    while (SDL_PollEvent(&evnt) == true) {
        /* Switch case to let us know what type of event it is*/
        switch (evnt.type) {
            /* If the user exits */
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
            /* On the user mouse motion*/
            case SDL_MOUSEMOTION:
                break;
        }
    }

}

/* Handles the drawing logic*/
void mainGame::drawGame() {

    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _colorProgram.use();

    GLuint timeLocation = _colorProgram.getUniformLocation("time");
    glUniform1f(timeLocation, _time);

    _sprite.draw();
    _colorProgram.unuse();

    SDL_GL_SwapWindow(_window);
}