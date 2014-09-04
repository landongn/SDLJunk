//
//  Game.cpp
//  sdl-hello
//
//  Created by thock on 8/9/14.
//  Copyright (c) 2014 landon. All rights reserved.
//

#include "Game.h"
#include <SDL2/SDL.h>

using namespace std;



bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) {
    if(SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
        mainWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);
        if(mainWindow != 0) {
            mainRenderer = SDL_CreateRenderer(mainWindow, -1, 0);

            if (mainRenderer != 0) {
                std::cout << "renderer created successfully \n";
                SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
            } else {
                std::cout << "renderer failed to create\n";
                return false;
            }
        } else {
            std::cout << "Window failure. \n";
            return false;
        }
        std::cout << "game running.\n";
        gameRunning = true;
    }
    return true;
}


void Game::render() {
    SDL_RenderClear(this->mainRenderer);
    SDL_RenderPresent(this->mainRenderer);
}

bool Game::running() {
    return this->gameRunning;
}

void Game::update() {
    
}

void Game::clean() {
    std::cout << "cleaning game\n";
    SDL_DestroyWindow(this->mainWindow);
    SDL_DestroyRenderer(this->mainRenderer);
    SDL_Quit();
}

void Game::handleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                this->gameRunning = false;
                break;
            default:
                break;
        }
    }
}