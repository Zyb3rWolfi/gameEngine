//
// Created by Zyb3rWolfi on 08/01/2024.
//

#ifndef UNTITLED_MAINGAME_H
#define UNTITLED_MAINGAME_H
#include <SDL.h>
#include<GLEW.h>
#include "sprites.h"
#include "GLSLProgram.h"
enum class GameState {PLAY, EXIT};

class mainGame {

    public:
        mainGame();
        ~mainGame();

        void run();

    private:
        void initSystems();
        void initShaders();
        void gameLoop();
        void processInput();
        void drawGame();
        SDL_Window* _window;
        int _screenWidth;
        int _screenHeight;

        GameState _gameState;
        sprites _sprite;
        GLSLProgram _colorProgram;

        float _time;

};


#endif //UNTITLED_MAINGAME_H
