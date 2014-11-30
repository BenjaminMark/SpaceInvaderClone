#pragma once

#include "GameObject.h"
#include <string>

class Projectile : public GameObject
{
public:
	virtual ~Projectile();

	static void newProjectile(std::string texturePath, Vector2 startPos, Vector2 direction);
	virtual void update();

protected:
	Vector2 direction;

	Projectile(std::string texturePath, Vector2 startPos, Vector2 direction);
};

