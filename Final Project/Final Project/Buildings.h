#pragma once
#include <SFML/Graphics.hpp>
#include "Textures.h"
#include "GameObject.h"

class Buildings : public GameObject
{
public:
	void Init(sf::Texture& texture, sf::Sprite& sprite, sf::IntRect& textureSize);
	void Draw() override;
	void Update() override;
	void MouseUp() override;

	void SelectBuilding();

	void Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites, bool isDead);
	void CheckIfSelected();
	void SetPosition(sf::Vector2f pos);

private:

};

