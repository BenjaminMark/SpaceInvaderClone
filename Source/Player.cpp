#include "Player.h"

std::vector<Texture*> Player::playerTextures = std::vector<Texture*>();

Player::Player(PlayerTexture texture_) : GameObject(LAYER_ACTORS)
{
	texture = playerTextures[texture_];
}


Player::~Player()
{
}

void Player::update()
{

}

bool Player::loadTextures(std::string basePath)
{
	for (int i = 0; i < NUM_PLAYERTEXTURES; ++i){
		Texture* tempTex = new Texture();
		bool success = tempTex->load(basePath + "_" + std::to_string(i) + ".png");
		playerTextures.push_back(tempTex);
		if (!success){
			printf("Failed to Load Player Texture: %d", i);
			return false;
		}
	}
	return true;
}

void Player::cleanTextures()
{
	for (int i = 0; i < NUM_PLAYERTEXTURES; ++i){
		delete playerTextures[i];
	}
}