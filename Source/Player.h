#pragma once

#include "GameObject.h"
#include "InputEvent.h"


class Player : public GameObject
{
public:
	Player(std::string texturePath, Vector2 startPos);
	virtual ~Player();

	virtual void update() override;
	static void newPlayer(std::string texturePath, Vector2 startPos);

protected:
	virtual void handleInput(std::shared_ptr<InputEvent> inputEvent);

	void movePlayer();
};