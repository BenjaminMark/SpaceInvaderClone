#include "Background.h"


Background::Background(BackgroundTextureType texType) : GameObject(LAYER_BACKGROUND)
{
	texture = std::make_shared<Texture>(); //Needs to be removed if background is expanded to work like other entities
	texture->load("Data/background.png");
}


Background::~Background()
{
	
}

void Background::newBackground(BackgroundTextureType texType)
{
	std::shared_ptr<GameObject> object = std::make_shared<Background>(texType);
	gameObjectList.emplace(object->layer, object);
}

void Background::update()
{

}
