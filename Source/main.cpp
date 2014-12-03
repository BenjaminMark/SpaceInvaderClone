#include "SpaceInvaderClone.h"
#include "SDL.h"
#include <SDL_ttf.h>
#include "SDL_mixer.h"
#include "SDL_image.h"

bool initSystems()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Error Initializing SDL: %s\n", SDL_GetError());
		return false;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		printf("Error initializing SDL_Image: %s\n", IMG_GetError());
		return false;
	}

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_Mixer could not be initialized:", Mix_GetError());
		return false;
	}
	return true;
}

void quitSystems()
{
	Mix_Quit();
	SDL_Quit();
	TTF_Quit();
	IMG_Quit();
}

int main(int argc, char* argv[])
{
	if (!initSystems()){
		return 1;
	}
	int retval = 0;
	while (retval == 0){
		SpaceInvaderClone game;
		retval = game.run();
	}
	quitSystems();
	return 0;
}

