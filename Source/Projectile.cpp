#include "Projectile.h"
#include "Constants.h"
#include "CollisionEvent.h"



Projectile::Projectile(std::string texturePath, Vector2 startPos, float rotation_, int speed_)
	: GameObject(LAYER_PROJECTILE, Texture::load(texturePath), true, startPos), rotation(rotation_), speed(speed_), direction(Vector2(0, 1))
{
	direction.rotate(rotation);
}


Projectile::~Projectile()
{
}

std::weak_ptr<Projectile> Projectile::newProjectile(std::string texturePath, Vector2 startPos, float rotation_, int speed_)
{
	std::shared_ptr<Projectile> object= std::make_shared<Projectile>(texturePath, startPos, rotation_, speed_);
	GameObject::registerObject(object);

	return std::weak_ptr<Projectile>(object);
}

void Projectile::update()
{
	move(direction * speed);

	while (!eventQueue.empty()){
		auto curEvent = eventQueue.front();
		eventQueue.pop();

		if (curEvent->type == EVENT_COLLISION){
			std::shared_ptr<CollisionEvent> colEvent = std::dynamic_pointer_cast<CollisionEvent>(curEvent);

			//Projectiles shouldn't destroy other projectiles
			if (colEvent->senderLayer != LAYER_PROJECTILE){
				alive = false;
				collisionEnabled = false;
			}
		}
	}
}

void Projectile::render()
{
	if (texture){
		texture->render(position, rotation);
	}
}