#include "game.h"

void Game::loadMediaPacman(){

	bool success = true;

	//Load sprite sheet texture
	if( !pacman.loadFromFile( "14_animated_sprites_and_vsync/foo.png" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		pacman->setSpriteClips();
	}
	
	return success;
}

void Game::close(){

	//Destroy window	
	SDL_DestroyRenderer( this->gRenderer );
	SDL_DestroyWindow( this->gWindow );
	this->gWindow = NULL;
	this->gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

}

bool Game::init(){

    // Initialization flag
    bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		this->gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( this->gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			this->gRenderer = SDL_CreateRenderer( this->gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( this->gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( this->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool Game::initPacman(){
	return this->loadMediaPacman();
}

void Game::close()
{
	//Free loaded images
	pacmac->free();

	//Destroy window	
	SDL_DestroyRenderer( this->gRenderer );
	SDL_DestroyWindow( this->gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Game::start(){
    
	/Start up SDL and create window
	if( !this->init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !this->initPacman() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Current animation frame
			int frame = 0;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}
                
                // Update pacman's action
                this->pacman->renderCurrentAction(frame, gRenderer)

				//Update screen
				SDL_RenderPresent( gRenderer );

				//Go to next frame
				++frame;

				//Cycle animation
				if( frame / 4 >= WALKING_ANIMATION_FRAMES )
				{
					frame = 0;
				}
			}
		}
	}

	//Free resources and close SDL
	close();
}
