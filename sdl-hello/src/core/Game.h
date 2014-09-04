//
//  Game.h
//  sdl-hello
//
//  Created by thock on 8/9/14.
//  Copyright (c) 2014 landon. All rights reserved.
//

#ifndef __sdl_hello__Game__
#define __sdl_hello__Game__

#include <iostream>
#include <SDL2/SDL.h>

class Game {
public:
    Game() {}
    ~Game() {}
    
    bool init (const char* title, int xpos, int ypos, int width, int height, int flags);
    void render();
    void update();
    void handleEvents();
    void clean();
    bool running();
    
private:
    bool gameRunning;
    SDL_Window* mainWindow;
    SDL_Renderer* mainRenderer;
};

#endif /* defined(__sdl_hello__Game__) */
