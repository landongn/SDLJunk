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
    void loadImage(std::string name);
    std::string getPath(std::string name);
    void renderTexture(SDL_Texture* tex, SDL_Renderer* renderer, int x, int y);
    void render();
    void update();
    void handleEvents();
    void clean();
    bool running();
    
private:
    bool gameRunning;
    char* data_path = NULL;
    SDL_Window* mainWindow;
    SDL_Renderer* mainRenderer;
    SDL_Texture* mainTexture;
    int m_x = 1;
    int m_y = 1;
};

#endif /* defined(__sdl_hello__Game__) */
