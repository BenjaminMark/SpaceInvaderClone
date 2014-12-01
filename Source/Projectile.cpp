#include "Projectile.h"
#include "Constants.h"



Projectile::Projectile(std::string texturePath, Vector2 startPos, Vector2 direction_, int speed_) 
	: GameObject(LAYER_PROJECTILE, Texture::load(texturePath), true, startPos), direction(direction_), speed(speed_)
{

}


Projectile::~Projectile()
{
}

void Projectile::newProjectile(std::string texturePath, Vector2 startPos, Vector2 direction_, int speed_)
{
	Projectile* tempPtr = new Projectile(texturePath, startPos, direction_, speed_);
	std::shared_ptr<GameObject> object(tempPtr);
	GameObject::registerObject(object);
}

void Projectile::update()
{
	move(direction * speed);

	while (!eventQueue.empty()){
		auto curEvent = eventQueue.front();
		eventQueue.pop();

		if (curEvent->type == EVENT_COLLISION){
			alive = false;
			collisionEnabled = false;
		}
	}
}