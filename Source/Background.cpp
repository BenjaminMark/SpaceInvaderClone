#include "Background.h"


Background::Background() : GameObject(LAYER_BACKGROUND)
{
	texture = new Texture(); //Needs to be removed if background is expanded to work like other entities
	texture->load("Data/background.png");
}


Background::~Background()
{
	delete texture; //Needs to be removed if background is expanded to work like other entities
}
