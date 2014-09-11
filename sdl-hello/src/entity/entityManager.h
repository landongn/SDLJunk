//
//  entityManager.h
//  sdl-hello
//
//  Created by thock on 8/9/14.
//  Copyright (c) 2014 landon. All rights reserved.
//

#ifndef __sdl_hello__entityManager__
#define __sdl_hello__entityManager__

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "entity.h"

class EntityManager {
    std::vector<Entity*> _entities;
    
public:
    EntityManager();
    ~EntityManager();
    
    void createEntity();
    void render(SDL_Renderer *renderer);
};

#endif /* defined(__sdl_hello__entityManager__) */
