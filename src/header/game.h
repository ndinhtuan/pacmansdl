#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include "pacman.h"

class Game{
    
public:
    //Starts up SDL and creates window
    bool init();
    //Frees media and shuts down SDL
    void close();
    
    SDL_Window* getWindow(){ return this->gWindow;}
    SDL_Renderer* getRenderer(){ return this->gRenderer;}

    // Begin intergrating pacman into game

    bool initPacman();
    void close();
    void start();

private:
    
    bool loadMediaPacman();

private:
    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;
    
    //The window renderer
    SDL_Renderer* gRenderer = NULL;

    Pacman *pacman = NULL;
}
#endif
