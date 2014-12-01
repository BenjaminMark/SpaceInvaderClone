#include "SpaceInvaderClone.h"
#include "GameObject.h"
#include "Background.h"
#include "Player.h"
#include "ScoreCounter.h"
#include "Enemy.h"
#include "SDL_TTF.h"
#include "Timer.h"


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

		eManager.manageEnemies();

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

	if (!Texture::initRendering()){
		return false;
	}

	initObjects();

	return true;
}

void SpaceInvaderClone::cleanUp()
{
	Texture::cleanUpRendering();
	
	SDL_Quit();
}


void SpaceInvaderClone::initObjects()
{	
	eManager.manageEnemies();

	Player::newPlayer("Data/Player/player_0.png", PLAYER_STARTPOS);
	Background::newBackground("Data/background_0.png");
	ScoreCounter::newScoreCounter();
}

