#include "SpaceInvaderClone.h"
#include "GameObject.h"
#include "Background.h"
#include "Player.h"
#include "SDL_TTF.h"
#include "Timer.h"

SDL_Window* SpaceInvaderClone::window = nullptr;
SDL_Renderer* SpaceInvaderClone::renderer = nullptr;

SpaceInvaderClone::SpaceInvaderClone()
{
}


SpaceInvaderClone::~SpaceInvaderClone()
{
}

int SpaceInvaderClone::run()
{
	if (!init()){
		return 1;
	}

	bool quit = false;
	Timer frameTimer;

	while (!quit){
		frameTimer.start();
		quit = inputhandler.handleEvents();

		GameObject::updateAll();

		GameObject::renderAll();
		if (frameTimer.getTicks() < TICKS_PER_FRAME){
			SDL_Delay(TICKS_PER_FRAME - frameTimer.getTicks());
		}
	}

	cleanUp();

	return 0;
}


bool SpaceInvaderClone::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Error Initializing SDL: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("Space Attackers", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		printf("Error creating window: %s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		printf("Error creating renderer: %s\n", SDL_GetError());
		return false;
	}
	
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//Initialize PNG loading
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

	handleTextures(false);
	initObjects();

	return true;
}

void SpaceInvaderClone::cleanUp()
{
	handleTextures(true);

	SDL_DestroyRenderer(SpaceInvaderClone::renderer);
	SDL_DestroyWindow(SpaceInvaderClone::window);

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void SpaceInvaderClone::handleTextures(bool cleanUp)
{
	if (!cleanUp){
		Player::loadTextures("Data/Player/playerTexture");
		//Expand here with more gameobject classes
	}
	else {
		Player::cleanTextures();
	}
}

void SpaceInvaderClone::initObjects()
{	
	Player::newPlayer(PLAYERTEX_0);
	Background::newBackground(BACKGROUNDTEX_0);
}