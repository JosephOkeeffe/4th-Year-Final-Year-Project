#ifndef GAMEOBJ_H
#define GAMEOBJ_H
#include <SFML/Graphics.hpp>
#include "Textures.h"

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

	virtual void Draw() { window->draw(body); }
	virtual void Update() {}
	virtual void MouseUp() {}

	void SetTexture(std::string name) 
	{ 
		texture = Textures::GetInstance().GetTexture(name);
		body.setTexture(texture);
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
