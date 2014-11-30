#include "Enemy.h"
#include "EventHandler.h"
#include "ScoreEvent.h"

int Enemy::numEnemies = 0;

Enemy::Enemy(std::string texturePath, Vector2 startPos) : GameObject(LAYER_ACTORS, Texture::load(texturePath), true, startPos)
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
			this->alive = false;
			EventHandler::raiseEvent(std::make_shared<ScoreEvent>(scoreValue));
		}
	}
}