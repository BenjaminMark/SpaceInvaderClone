#pragma once

#include "GameObject.h"
#include "InputEvent.h"

enum PlayerTextureType;

class Player : public GameObject
{
public:
	Player(PlayerTextureType texture_);
	virtual ~Player();

	virtual void update() override;
	static void newPlayer(PlayerTextureType);
	static bool loadTextures(std::string basePath);
	static void cleanTextures();

protected:
	static std::vector<std::shared_ptr<Texture>> playerTextures;
	virtual void handleInput(std::shared_ptr<InputEvent> inputEvent);
	
};

//This should most likely be in a config file
enum PlayerTextureType {
	PLAYERTEX_0 = 0,
	NUM_PLAYERTEXTURES
};
