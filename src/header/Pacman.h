#ifndef PACMAN_H
#define PACMAN_H

#include <SDL2/SDL.h>
#include <string.h>
#include <config.h>

class Pacman {

public:

    Pacman();
    ~Pacman();
    
    // load image for character pacman
    bool loadFromFile(std::string &path, SDL_Renderer* gRenderer);

    // free texture
    void free();

    // set bending mode
    void setBlendMode( SDL_BlendMode blending );
	//Set alpha modulation
    void setAlpha( Uint8 alpha );
    //Renders texture at given point
	void render( int x, int y, SDL_Rect* clip = NULL, SDL_Renderer* gRenderer);

    void setSpriteClips();

    // Begin playing

    void renderCurrentAction(int frame, SDL_Renderer* gRenderer);
	
	// get Image dimensions
	int getWidth() {return this->width;}
	int getHeight() {return this->height;}
	
private:
    //Walking animation
    const int WALKING_ANIMATION_FRAMES = 4;
    SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
	
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
}

#endif
