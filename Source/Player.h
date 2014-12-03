#pragma once

#include "GameObject.h"
#include "InputEvent.h"
#include "UpgradeState.h"
#include "ExplosiveProjectile.h"


class Player : public GameObject
{
public:
	Player(std::string texturePath, Vector2 startPos);
	virtual ~Player();

	static std::weak_ptr<Player> newPlayer(std::string texturePath, Vector2 startPos);

	virtual void update() override;
	static void setUpgradeState(UpgradeState state);

protected:
	static UpgradeState upgradeState;
	bool detonate;
	std::weak_ptr<ExplosiveProjectile> currentExplosive;

	virtual void handleInput(std::shared_ptr<InputEvent> inputEvent);
	void movePlayer();
	void shoot();
};