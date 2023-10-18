#include "Textures.h"

Textures::Textures()
{
	SetupTextures();
}

void Textures::SetupTextures()
{

	warriorTexture.loadFromFile("./assets/images/warrior.png");
	textureMap["warrior"] = warriorTexture;

}