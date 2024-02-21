#pragma once
#include <SFML/Graphics.hpp>
#include "Buildings.h"
#include "BuildingUI.h"
#include "Shader.h"

class Headquarters : public Buildings 
{
public:
	Headquarters(sf::Vector2f pos);
	void Update() override;
	void Draw() override;
	void MouseRelease() override;
	void ChangeSelectedColour();
private:

	int textureWidth = 57;
	int textureHeight = 76;
	int currentFrameX = textureWidth * 2;
	int currentFrameY = 0;
	int amountOfSprites = 2;


	void HandleRightClick(sf::Vector2f mousePosition);
	void UpdateControlHandles();
	void HandleMouseMovement(sf::Vector2f mousePosition);
	void HandleRightRelease();

	sf::RectangleShape rotateHandle;
	sf::RectangleShape scaleHandle;
	bool isRotating = false;
	bool isScaling = false;

	bool isYes = false;

	sf::Vector2f rotationHandleOffset;
	sf::Vector2f resizeHandleOffset;
	sf::Vector2f originalSize;

	Shader shader;
};

