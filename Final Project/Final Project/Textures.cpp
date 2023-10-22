#include "Textures.h"

Textures::Textures()
{
	SetupTextures();
}

void Textures::SetupTextures()
{

	warriorTexture.loadFromFile("./assets/images/warrior.png");
	textureMap["warrior"] = warriorTexture;

	archerTexture.loadFromFile("./assets/images/mage.png");
	textureMap["archer"] = archerTexture;

}