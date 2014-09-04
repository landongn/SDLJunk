//
//  main.cpp
//  sdl-hello
//
//  Created by thock on 8/8/14.
//  Copyright (c) 2014 landon. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "src/core/Game.h"


SDL_Window* mainWindow = 0;
SDL_Renderer* mainRenderer = 0;
bool gameRunning = false;

int main(int argc, const char * argv[]) {
    
    Game* _game = 0;
    _game = new Game();

    _game->init("Chapter 1", 100, 100, 720, 1280, 0);

    while(_game->running()) {
        _game->handleEvents();
        _game->update();
        _game->render();
    }
    _game->clean();
    
    return 0;
}

