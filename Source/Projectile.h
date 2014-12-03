#pragma once

#include "GameObject.h"
#include <string>

class Projectile : public GameObject
{
public:
	Projectile(std::string texturePath, Vector2 startPos, float rotation, int speed);
	virtual ~Projectile();

	static std::weak_ptr<Projectile> newProjectile(std::string texturePath, Vector2 startPos, float rotation, int speed);
	virtual void update();
	virtual void render();

protected:
	float rotation;
	Vector2 direction;
	int speed;
};

