#ifndef GAMEOBJ_H
#define GAMEOBJ_H
#include <SFML/Graphics.hpp>
#include "Textures.h"
#include "Globals.h"
#include "BuildingUI.h"
#include "HUD.h"
#include "Tile.h"
#include "Game.h"

#define Display_Text(x) std::cout << x << "\n";

class GameObject
{
private:
	static sf::RenderWindow* window;
	static sf::View* gameView;
	
public:

	Game* game;
	static Tile** tiles;

	static void SetWindow(sf::RenderWindow& _window) { window = &_window; }
	static void SetView(sf::View& _gameView) { gameView = &_gameView; }
	static void SetTiles(Tile** _tiles) {tiles = _tiles;}


	bool isSelected = false;
	sf::Sprite body;
	sf::Texture texture;
	sf::IntRect textureRect;

	sf::CircleShape detectionCircle;
	float detectionRadius = 100.0f;

	virtual void Draw() { window->draw(body); window->draw(detectionCircle); }
	virtual void Update() { detectionCircle.setPosition(body.getPosition());}
	virtual void MouseRelease() {}

	void InitDetectionCircle(int radius)
	{
		detectionCircle.setRadius(radius);
		detectionCircle.setOrigin(radius, radius);
		detectionCircle.setPosition(body.getPosition());
		detectionCircle.setFillColor(sf::Color::Transparent);
		detectionCircle.setOutlineThickness(1);
		detectionCircle.setOutlineColor(sf::Color(255, 0, 0, 255));
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
