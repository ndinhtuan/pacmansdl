#include "Pacman.h"
#include "SDL2/SDL_image.h"

Pacman::Pacman()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Pacman::~Pacman()
{
	//Deallocate
	free();
}

void Pacman::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void Pacman::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void Pacman::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void Pacman::render( int x, int y, SDL_Rect* clip, SDL_Renderer* gRenderer)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

void Pacman::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

bool Pacman::loadFromFile(std::string &path, SDL_Renderer* gRenderer){
	//Get rid of preexisting texture
	this->freeTexture();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void Pacman::setSpriteClips(){

	gSpriteClips[ 0 ].x =   0;
	gSpriteClips[ 0 ].y =   0;
	gSpriteClips[ 0 ].w =  64;
	gSpriteClips[ 0 ].h = 205;

	gSpriteClips[ 1 ].x =  64;
	gSpriteClips[ 1 ].y =   0;
	gSpriteClips[ 1 ].w =  64;
	gSpriteClips[ 1 ].h = 205;
	
	gSpriteClips[ 2 ].x = 128;
	gSpriteClips[ 2 ].y =   0;
	gSpriteClips[ 2 ].w =  64;
	gSpriteClips[ 2 ].h = 205;

	gSpriteClips[ 3 ].x = 196;
	gSpriteClips[ 3 ].y =   0;
	gSpriteClips[ 3 ].w =  64;
	gSpriteClips[ 3 ].h = 205;
}

void Pacman::renderCurrentAction(int frame, SDL_Renderer* gRenderer){

    // clear screen
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );

    // Render pacman action
    // Do action 
    SDL_Rect* currentClip = &gSpriteClips[ frame / 4 ];
    this->render( ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, currentClip, gRenderer);
}











