#pragma once

#include "EventHandler.h"
#include "Constants.h"
#include "EnemyManager.h"

class SpaceInvaderClone
{
public:
	SpaceInvaderClone();
	~SpaceInvaderClone();

	int run();

private:
	EventHandler inputhandler;
	EnemyManager eManager;

	bool init();
	void cleanUp();
	void initObjects();
	void spawnEnemies();
};

