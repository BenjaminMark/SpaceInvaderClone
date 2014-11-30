#include "Background.h"


Background::Background(std::string texturePath) : GameObject(LAYER_BACKGROUND)
{
	texture = Texture::load(texturePath);
}


Background::~Background()
{
	
}

void Background::newBackground(std::string texturePath)
{
	GameObject::registerObject(std::make_shared<Background>(texturePath));
}

void Background::update()
{

}
