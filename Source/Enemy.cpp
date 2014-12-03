#include "Enemy.h"
#include "EventHandler.h"
#include "ScoreEvent.h"
#include "Constants.h"
#include "CollisionEvent.h"
#include "Projectile.h"
#include "AudioEvent.h"
#include "SoundType.h"

int Enemy::numEnemies = 0;
int Enemy::currentDelay = ENEMY_MOVE_DELAY;

Enemy::Enemy(std::string texturePath, Vector2 startPos) : GameObject(LAYER_ENEMY, Texture::load(texturePath), true, startPos), scoreValue(ENEMY_SCORE_VALUE),
	direction(Vector2(1, 0)), actionTimer(0), moveCount(0)
{
	numEnemies++;
}


Enemy::~Enemy()
{
	numEnemies--;
}

std::weak_ptr<Enemy> Enemy::newEnemy(std::string texturePath, Vector2 startPos)
{
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(texturePath, startPos);
	GameObject::registerObject(enemy);
	return std::weak_ptr<Enemy>(enemy);
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
				EventHandler::raiseEvent(std::make_shared<AudioEvent>(SOUND_ENEMYDEATH));
				alive = false;
				collisionEnabled = false;
				EventHandler::raiseEvent(std::make_shared<ScoreEvent>(false, scoreValue));
			}
		}
	}

	if (actionTimer < currentDelay){
		actionTimer++;
	}
	else {
		actionTimer = 0;
		moveEnemy();
	}
}

void Enemy::shoot()
{
	Projectile::newProjectile("Data/Projectiles/projectile_0.png", Vector2(position.x + dimensions.x / 2, position.y + dimensions.y + 20), 0.0, ENEMY_PROJECTILE_SPEED);
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