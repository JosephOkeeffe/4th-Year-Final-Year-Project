#ifndef GAMEOBJ_H
#define GAMEOBJ_H
#include <SFML/Graphics.hpp>
#include "Textures.h"
#include "Globals.h"
#include "BuildingUI.h"

#define Display_Text(x) std::cout << x << "\n";

class GameObject
{
private:
	static sf::RenderWindow* window;
	static sf::View* gameView;
public:
	static void SetWindow(sf::RenderWindow& _window) { window = &_window; }
	static void SetView(sf::View& _gameView) { gameView = &_gameView; }

	sf::Sprite body;
	sf::Texture texture;
	sf::IntRect textureRect;

	sf::CircleShape detectionCircle;
	float detectionRadius = 100.0f;

	virtual void Draw() { window->draw(body); window->draw(detectionCircle); }
	virtual void Update() { detectionCircle.setPosition(body.getPosition());}
	virtual void MouseUp() {}

	void InitDetectionCircle()
	{
		detectionCircle.setRadius(detectionRadius);
		detectionCircle.setOrigin(detectionRadius, detectionRadius);
		detectionCircle.setPosition(body.getPosition());
		detectionCircle.setFillColor(sf::Color(255, 0, 0, 50));
	}

	void SetTexture(sf::Texture tex)
	{
		texture = tex;
		body.setTexture(texture);
	}

	void SetTextureRect(sf::IntRect rect)
	{
		textureRect = rect;
		body.setTextureRect(textureRect);
	}

	sf::RenderWindow* GetWindow() { return window; }
	sf::View* GetView() { return gameView; }
};

#endif
