#include "ExplosiveProjectile.h"
#include "CollisionEvent.h"
#include "AudioEvent.h"
#include "SoundType.h"
#include "EventHandler.h"


ExplosiveProjectile::ExplosiveProjectile(std::string texturePath, Vector2 startPos, float rotation, int speed) : 
	Projectile(texturePath, startPos, rotation, speed)
{
}


ExplosiveProjectile::~ExplosiveProjectile()
{
}


std::weak_ptr<ExplosiveProjectile> ExplosiveProjectile::newExplosiveProjectile(std::string texturePath, Vector2 startPos, float rotation, int speed)
{
	std::shared_ptr<ExplosiveProjectile> object = std::make_shared<ExplosiveProjectile>(texturePath, startPos, rotation, speed);
	GameObject::registerObject(object);

	return std::weak_ptr<ExplosiveProjectile>(object);
}

void ExplosiveProjectile::update()
{
	move(direction * speed);

	while (!eventQueue.empty()){
		auto curEvent = eventQueue.front();
		eventQueue.pop();

		if (curEvent->type == EVENT_COLLISION){
			std::shared_ptr<CollisionEvent> colEvent = std::dynamic_pointer_cast<CollisionEvent>(curEvent);

			//Projectiles shouldn't destroy other projectiles
			if (colEvent->senderLayer != LAYER_PROJECTILE){
				detonate();
			}
		}
	}
}

void ExplosiveProjectile::detonate()
{
	for (int angle = 45; angle < 360; angle += 30){
			Projectile::newProjectile(texture->getPath(), position, static_cast<float>(angle), speed);
	}
	EventHandler::raiseEvent(std::make_shared<AudioEvent>(SOUND_EXPLOSION));
	alive = false;
	collisionEnabled = false;
}