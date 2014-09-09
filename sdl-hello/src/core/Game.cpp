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
#include <JavaScriptCore/JavaScriptCore.h>

static const uint8_t SUCCESS = 0;

static JSValueRef console_log(JSContextRef ctx, JSObjectRef /*function*/, JSObjectRef thisObject, size_t /*argumentCount*/, const JSValueRef[] /*arguments*/, JSValueRef* /*exception*/);

JSClassRef ConsoleClass()
{
    static JSStaticFunction staticFunctions[] = {
        { "log", console_log, kJSPropertyAttributeNone }
    };
    
    JSClassDefinition classDefinition = {
        0, kJSClassAttributeNone, "console", 0, 0, staticFunctions,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    
    static JSClassRef consoleClass = JSClassCreate(&classDefinition);
    return consoleClass;
}

/**
 * The callback from JavaScriptCore.  We told JSC to call this function
 * whenever it sees "console.log".
 */
static JSValueRef console_log(JSContextRef ctx, JSObjectRef /*function*/, JSObjectRef thisObject, size_t argumentCount, const JSValueRef* arguments, JSValueRef* exception)
{
    if (!JSValueIsObjectOfClass(ctx, thisObject, ConsoleClass()))
        return JSValueMakeUndefined(ctx);
    
    if (argumentCount < 1)
        return JSValueMakeUndefined(ctx);
    
    // Convert the result into a string for display.
    if (!JSValueIsString(ctx, arguments[0]))
        return JSValueMakeUndefined(ctx);
    
    JSStringRef temp = JSValueToStringCopy (ctx, arguments[0], exception);
    if (exception && *exception)
        return JSValueMakeUndefined(ctx);
    
    char otherStr[1024];
    JSStringGetUTF8CString(temp, otherStr, sizeof(char[1024]));
    std::cout << "Got console log " << otherStr << std::endl;
    
    JSStringRelease(temp);
    
    return JSValueMakeUndefined(ctx);
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != SUCCESS) {
        std::cout << "SDL_Init failure!" << std::endl;
        return false;
    }
    
    mainWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);
    if(!mainWindow) {
        std::cout << "SDL_CreateWindow failure!" << std::endl;
        return false;
    }
    
    mainRenderer = SDL_CreateRenderer(mainWindow, -1, 0);
    if (!mainRenderer) {
        std::cout << "SDL_CreateRenderer failure!" << std::endl;
        return false;
    }
    
    std::cout << "Renderer created successfully!" << std::endl;
    SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
    
    std::cout << "Game running!" << std::endl;
    loadImage();
    gameRunning = true;
    
    JSGlobalContextRef ctx = JSGlobalContextCreate(NULL);
    
    JSObjectRef global = JSContextGetGlobalObject(ctx);
    assert(global);
    
    JSClassRef consoleClass = ConsoleClass();
    assert(consoleClass);
    
    JSObjectRef scriptObj = JSObjectMake(ctx, consoleClass, static_cast<void*>(this));
    assert(scriptObj);
    
    JSStringRef consoleName = JSStringCreateWithUTF8CString("console");
    JSValueRef except;
    JSObjectSetProperty(ctx, global, consoleName, scriptObj, kJSPropertyAttributeNone, &except);
    
    std::string functionString = "function main() { var foo = 'bar'; console.log(foo); return foo; }; main(); 'foo';";
    JSStringRef jsString = JSStringCreateWithUTF8CString(functionString.c_str());
    
    JSValueRef error;
    
    JSValueRef ref = JSEvaluateScript(ctx, jsString, NULL, NULL, 1, &error);
    
    JSStringRef str = JSValueToStringCopy(ctx, error, NULL);
    char myStr[1024];
    JSStringGetUTF8CString(str, myStr, sizeof(char[1024]));
    
    JSStringRef strRef = JSValueToStringCopy(ctx, ref, NULL);
    char otherStr[1024];
    JSStringGetUTF8CString(strRef, otherStr, sizeof(char[1024]));
    
    JSStringRelease(strRef);
    JSStringRelease(str);
    
    return true;
}

std::string getPath(std::string name) {
    char path[1024];
    uint32_t size = sizeof(char[1024]);
    std::string result;
    
    if (_NSGetExecutablePath(path, &size) != SUCCESS) {
        std::cout << "Buffer too small, need size " << size << std::endl;
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
    
    std::cout << "Location is " << imagePath.c_str() << std::endl;
    
    SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
    if (!bmp) {
        SDL_DestroyRenderer(mainRenderer);
        SDL_DestroyWindow(mainWindow);
        std::cout << "Failed to create image." << std::endl;
        SDL_Quit();
    }
    
    mainTexture = SDL_CreateTextureFromSurface(mainRenderer, bmp);
    SDL_FreeSurface(bmp);
    if (!mainTexture) {
        SDL_DestroyRenderer(mainRenderer);
        SDL_DestroyWindow(mainWindow);
        std::cout << "Failed to create texture." << std::endl;
        SDL_Quit();
    }
    
    std::cout << "created texture successfully." << std::endl;
}

void Game::renderTexture(SDL_Texture *tex, SDL_Renderer *renderer, int x, int y) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, tex, NULL, &rect);
}

void Game::render() {
    if (gameRunning) {
        SDL_RenderClear(mainRenderer);
    
        if (mainTexture) {
            renderTexture(mainTexture, mainRenderer, m_x, m_y);
            //m_x += 1;
        }
    
        SDL_RenderPresent(mainRenderer);
    }
}

bool Game::running() {
    return gameRunning;
}

void Game::update() {
    
}

void Game::clean() {
    std::cout << "cleaning game" << std::endl;
    SDL_DestroyWindow(mainWindow);
    SDL_DestroyRenderer(mainRenderer);
    SDL_Quit();
}

void Game::handleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                gameRunning = false;
                break;
            case SDL_KEYDOWN:
                gameRunning = false;
                break;
            default:
                break;
        }
    }
}