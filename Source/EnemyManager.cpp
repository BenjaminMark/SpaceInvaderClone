#include "EnemyManager.h"
#include "Constants.h"
#include "stdlib.h"

EnemyManager::EnemyManager()
{
	currentDelay = rand() % ENEMY_SHOT_DELAY_RANGE + ENEMY_SHOT_DELAY_MIN;
	shotTimer.start();
}


EnemyManager::~EnemyManager()
{
}

void EnemyManager::manageEnemies()
{
	if (Enemy::getNumEnemies() == 0){
		if (Enemy::currentDelay > 10){
			Enemy::currentDelay -= ENEMY_MOVE_DELAY_DECREASE;
		}
		else{
			Enemy::currentDelay -= 1;
		}
		spawnEnemies();
	}

	shootPlayer();
}


void EnemyManager::spawnEnemies()
{
	Vector2 curEnemyPos = ENEMY_STARTPOS;
	enemyStacks.clear();

	for (int i = 0; i < ENEMY_NUM_PER_ROW; ++i){
		std::stack<std::weak_ptr<Enemy>> curStack;
		for (int j = 0; j < ENEMY_NUM_ROWS; j++){
			curStack.push(Enemy::newEnemy("Data/Enemies/enemy_0.png", curEnemyPos));
			curEnemyPos.y += ENEMY_ROW_DISTANCE;
		}
		curEnemyPos.y = ENEMY_STARTPOS.y;
		curEnemyPos.x += ENEMY_HOR_DISTANCE;
		enemyStacks.push_back(curStack);
	}
}

void EnemyManager::shootPlayer()
{
	if (shotTimer.getTicks() > currentDelay){
		int columnToShoot = rand() % ENEMY_NUM_PER_ROW;

		while (!enemyStacks[columnToShoot].empty()){
			if (!enemyStacks[columnToShoot].top().expired()){
				enemyStacks[columnToShoot].top().lock()->shoot();
				break;
			}
			else {
				enemyStacks[columnToShoot].pop();
			}
		}
		shotTimer.start();
		currentDelay = rand() % ENEMY_SHOT_DELAY_RANGE + ENEMY_SHOT_DELAY_MIN;
	}
}