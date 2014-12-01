#include "Enemy.h"
#include "EventHandler.h"
#include "ScoreEvent.h"
#include "Constants.h"
#include "CollisionEvent.h"

int Enemy::numEnemies = 0;

Enemy::Enemy(std::string texturePath, Vector2 startPos) : GameObject(LAYER_ENEMY, Texture::load(texturePath), true, startPos), scoreValue(0),
direction(Vector2(1, 0)), actionTimer(0), moveCount(0)
{
	numEnemies++;
}


Enemy::~Enemy()
{
	numEnemies--;
}

void Enemy::newEnemy(std::string texturePath, Vector2 startPos)
{
	GameObject::registerObject(std::make_shared<Enemy>(texturePath, startPos));
}

void Enemy::update()
{
	while (!eventQueue.empty()){
		auto curEvent = eventQueue.front();
		eventQueue.pop();

		if (curEvent->type == EVENT_COLLISION){
			std::shared_ptr<CollisionEvent> colEvent = std::dynamic_pointer_cast<CollisionEvent>(curEvent);

			//Bit of a hack to get around movement not happening simultaneously. Enemies should never need to collide anyway.
			if (colEvent->senderLayer != LAYER_ENEMY){
				this->alive = false;
				EventHandler::raiseEvent(std::make_shared<ScoreEvent>(scoreValue));
			}
		}
	}

	if (actionTimer < FPS_CAP/3){
		actionTimer++;
	}
	else {
		actionTimer = 0;
		moveEnemy();
	}
}

void Enemy::moveEnemy()
{
	if (moveCount < ENEMY_NUM_MOVES){
		move(direction*ENEMY_MOVE_DIST_HOR);
		moveCount++;
	}
	else {
		move(Vector2(0, 1)*ENEMY_MOVE_DIST_VERT);
		direction *= -1;
		moveCount = 0;
	}
}