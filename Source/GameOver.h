#pragma once

#include "Texture.h"
#include <memory>

class GameOver
{
public:
	GameOver();
	~GameOver();

	int waitForPlayer();

private:
	std::shared_ptr<Texture> gameoverScreen;
};

