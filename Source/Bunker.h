#pragma once
#include "GameObject.h"
class Bunker : public GameObject
{
public:
	Bunker(std::string texturePath, Vector2 startPos);
	virtual ~Bunker();

	static void newBunker(std::string texturePath, Vector2 startPos);

	virtual void update();

private:
	int lives;
	int destructionState;
};

