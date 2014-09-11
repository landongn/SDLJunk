//
//  entity.h
//  sdl-hello
//
//  Created by Dan Ristic on 9/10/14.
//  Copyright (c) 2014 landon. All rights reserved.
//

#ifndef __sdl_hello__entity__
#define __sdl_hello__entity__

#include <iostream>
#include <SDL2/SDL.h>

class Entity {
public:
    Entity();
    ~Entity();
    
    void render(SDL_Renderer *renderer);
};

#endif /* defined(__sdl_hello__entity__) */
