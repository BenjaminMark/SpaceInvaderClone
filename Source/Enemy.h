#pragma once

#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy(std::string texturePath, Vector2 startPos);
	virtual ~Enemy();

	static void newEnemy(std::string texturePath, Vector2 startPos);
	static int getNumEnemies(){ return numEnemies; }
	virtual void update();

protected:
	static int numEnemies;
	const int scoreValue = 10;
	int actionTimer;
	int moveCount;
	Vector2 direction;

	void moveEnemy();
};

