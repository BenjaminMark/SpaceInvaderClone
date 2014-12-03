#pragma once
#include "Projectile.h"
class ExplosiveProjectile :
	public Projectile
{
public:
	ExplosiveProjectile(std::string texturePath, Vector2 startPos, float rotation, int speed);
	~ExplosiveProjectile();

	virtual void update();
	static std::weak_ptr<ExplosiveProjectile> newExplosiveProjectile(std::string texturePath, Vector2 startPos, float rotation, int speed);
	void detonate();
};

