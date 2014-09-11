//
//  entityManager.cpp
//  sdl-hello
//
//  Created by thock on 8/9/14.
//  Copyright (c) 2014 landon. All rights reserved.
//

#include "entityManager.h"

EntityManager::EntityManager() {
    
}

void EntityManager::createEntity() {
    _entities.push_back(new Entity());
}

void EntityManager::render(SDL_Renderer *renderer) {
    
}

EntityManager::~EntityManager() {
    
}