//
//  bindings.h
//  sdl-hello
//
//  Created by Dan Ristic on 9/8/14.
//  Copyright (c) 2014 landon. All rights reserved.
//

#ifndef __sdl_hello__bindings__
#define __sdl_hello__bindings__

#include "Game.h"
#include <JavaScriptCore/JavaScriptCore.h>
#include <JavaScriptCore/JSValueRef.h>

static JSValueRef console_log(JSContextRef ctx, JSObjectRef /*function*/, JSObjectRef thisObject, size_t /*argumentCount*/, const JSValueRef[] /*arguments*/, JSValueRef* /*exception*/);

JSClassRef ConsoleClass();

static JSValueRef create_image(JSContextRef ctx, JSObjectRef, JSObjectRef thisObject, size_t, const JSValueRef[], JSValueRef*);

JSClassRef EngineClass();

std::string loadData();

void doBindings(Game*);

#endif /* defined(__sdl_hello__bindings__) */
