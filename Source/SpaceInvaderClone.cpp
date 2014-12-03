#include "SpaceInvaderClone.h"
#include "GameObject.h"
#include "Background.h"
#include "Player.h"
#include "ScoreManager.h"
#include "Enemy.h"
#include "SDL_TTF.h"
#include "Timer.h"
#include "Bunker.h"
#include "GameOver.h"
#include "AudioMixer.h"
#include "SDL_mixer.h"

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

	int run = 1;
	Timer frameTimer;

	while (run > 0){
		frameTimer.start();
		run = inputhandler.handleEvents();

		GameObject::updateAll();

		eManager.manageEnemies();

		GameObject::renderAll();

		

		if (frameTimer.getTicks() < TICKS_PER_FRAME){
			SDL_Delay(TICKS_PER_FRAME - frameTimer.getTicks());
		}
	}

	if (run == 0){
		GameObject::clearAll();
		GameOver gameover;
		EventHandler::flushEvents();
		run = gameover.waitForPlayer();
	}

	cleanUp();

	return run;
}


bool SpaceInvaderClone::init()
{
	if (!Texture::initRendering()){
		return false;
	}

	initObjects();

	return true;
}

void SpaceInvaderClone::cleanUp()
{
	Texture::cleanUpRendering();
}


void SpaceInvaderClone::initObjects()
{	
	eManager.manageEnemies();

	Player::newPlayer("Data/Player/player_0.png", PLAYER_STARTPOS);
	Background::newBackground("Data/background_0.png");
	ScoreManager::newScoreCounter();
	AudioMixer::newAudioMixer();

	Bunker::newBunker("Data/Bunkers/bunker_0.png", BUNKER_STARTPOS);
	Bunker::newBunker("Data/Bunkers/bunker_0.png", Vector2(static_cast<float>(WINDOW_WIDTH - BUNKER_STARTPOS.x - 164), BUNKER_STARTPOS.y));
	Bunker::newBunker("Data/Bunkers/bunker_0.png", Vector2(static_cast<float>(WINDOW_WIDTH / 2 - 82), BUNKER_STARTPOS.y));
}

