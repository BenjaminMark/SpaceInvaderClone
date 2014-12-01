#pragma once

#include "GameObject.h"

class Enemy : public GameObject
{
public:
	static int currentDelay;

	Enemy(std::string texturePath, Vector2 startPos);
	virtual ~Enemy();

	static std::weak_ptr<Enemy> newEnemy(std::string texturePath, Vector2 startPos);
	static int getNumEnemies(){ return numEnemies; }
	virtual void update();
	virtual void shoot();

protected:
	static int numEnemies;
	const int scoreValue;
	int actionTimer;
	int moveCount;
	Vector2 direction;

	void moveEnemy();
};

