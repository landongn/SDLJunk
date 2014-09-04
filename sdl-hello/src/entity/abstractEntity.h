//
//  abstractEntity.h
//  sdl-hello
//
//  Created by thock on 8/9/14.
//  Copyright (c) 2014 landon. All rights reserved.
//

#ifndef __sdl_hello__abstractEntity__
#define __sdl_hello__abstractEntity__

#include <iostream>
#include <SDL2/SDL.h>

class abstractEntity {
    
    
public:
    
    
    virtual void update(double delta);
    virtual void render(double delta);
    virtual void destroy();
};

#endif /* defined(__sdl_hello__abstractEntity__) */
