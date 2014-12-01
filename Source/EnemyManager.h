#pragma once

#include "Enemy.h"
#include "Timer.h"
#include <stack>
#include <vector>

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void manageEnemies();

private:
	int currentDelay;
	Timer shotTimer;
	std::vector<std::stack<std::weak_ptr<Enemy>>> enemyStacks;

	void spawnEnemies();
	void shootPlayer();
};

