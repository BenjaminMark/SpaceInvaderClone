#pragma once

#include "GameObject.h"

enum PlayerTexture;

class Player : public GameObject
{
public:
	Player(PlayerTexture texture_);
	virtual ~Player();

	virtual void update() override;
	static bool loadTextures(std::string basePath);
	static void cleanTextures();

private:
	static std::vector<Texture*> playerTextures;

};

//This should most likely be in a config file
enum PlayerTexture {
	PLAYERTEX_0 = 0,
	NUM_PLAYERTEXTURES
};
