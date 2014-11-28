#pragma once
#include "GameObject.h"

enum BackgroundTextureType; 

class Background : public GameObject
{
public:

	Background(BackgroundTextureType texType);
	virtual ~Background();

	virtual void update();
	static void newBackground(BackgroundTextureType texType);
	

protected:
	
};

enum BackgroundTextureType{
	BACKGROUNDTEX_0 = 0,
	NUM_BACKGROUNDTEX
};