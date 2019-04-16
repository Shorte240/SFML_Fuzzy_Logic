#pragma once

#include <SFML/Graphics.hpp>

class FiniteCar
{
public:
	FiniteCar(sf::RenderWindow* hwnd);
	~FiniteCar();

	void Update(float dt);
	void GetLinePosition(sf::Vector2f linePos);
	void Render();

private:
	sf::RenderWindow* window;
	sf::RectangleShape line;
	float movementSpeed;
	sf::Vector2f linePosition;
	sf::Sprite carSprite;
	sf::Texture carTexture;
};

