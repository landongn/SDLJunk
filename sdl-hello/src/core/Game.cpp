//
//  Game.cpp
//  sdl-hello
//
//  Created by thock on 8/9/14.
//  Copyright (c) 2014 landon. All rights reserved.
//

#include "Game.h"
#include <SDL2/SDL.h>
#include <mach-o/dyld.h>

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
        loadImage();
        gameRunning = true;
    }
    return true;
}

std::string getPath(std::string name) {
    char path[1024];
    uint32_t size = sizeof(char[1024]);
    std::string result;
    
    if (_NSGetExecutablePath(path, &size) != 0) {
        printf("buffer too small; need size %u\n", size);
        realloc(path, size);
        _NSGetExecutablePath(path, &size);
    }
    
    result = std::string(path);
    size_t f = std::string(result).rfind("sdl-hello");
    result = result.replace(f, std::string("sdl-hello").length(), "");
    
    result = result + "Resources/" + name;
    
    return result;
}

void Game::loadImage() {
    std::string imagePath = getPath("hello.bmp");
    
    printf("Location is %s\n", imagePath.c_str());
    
    SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
    if (bmp == nullptr) {
        SDL_DestroyRenderer(mainRenderer);
        SDL_DestroyWindow(mainWindow);
        std::cout << "Failed to create image.\n";
        SDL_Quit();
    }
    
    mainTexture = SDL_CreateTextureFromSurface(mainRenderer, bmp);
    SDL_FreeSurface(bmp);
    if (mainTexture == nullptr) {
        SDL_DestroyRenderer(mainRenderer);
        SDL_DestroyWindow(mainWindow);
        std::cout << "Failed to create texture.\n";
        SDL_Quit();
    }
    
    std::cout << "created texture successfully";
}

void Game::renderTexture(SDL_Texture *tex, SDL_Renderer *renderer, int x, int y) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, tex, NULL, &rect);
}

void Game::render() {
    if (gameRunning == true) {
        SDL_RenderClear(this->mainRenderer);
    
        if (mainTexture != nullptr) {
            renderTexture(mainTexture, mainRenderer, m_x, m_y);
            //m_x += 1;
        }
    
        SDL_RenderPresent(this->mainRenderer);
    }
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
            case SDL_KEYDOWN:
                this->gameRunning = false;
                break;
            default:
                break;
        }
    }
}