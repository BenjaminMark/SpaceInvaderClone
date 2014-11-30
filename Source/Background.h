#pragma once
#include "GameObject.h"
#include <string>

enum BackgroundTextureType; 

class Background : public GameObject
{
public:

	Background(std::string texturePath);
	virtual ~Background();

	virtual void update();
	static void newBackground(std::string texturePath);
};

enum BackgroundTextureType{
	BACKGROUNDTEX_0 = 0,
	NUM_BACKGROUNDTEX
};