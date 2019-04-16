#pragma once

#include <SFML/Graphics.hpp>

class FiniteCar
{
public:
	FiniteCar(sf::RenderWindow* hwnd);
	~FiniteCar();

	void Update(float dt);
	void GetLinePosition(sf::Vector2f linePos);
	void MoveCar(float dt);
	void Render();

private:
	sf::RenderWindow* window;

	sf::Sprite carSprite;
	sf::Texture carTexture;

	enum CarStates
	{
		FarLeft = 0,
		Left = 1,
		Centre = 2,
		Right = 3,
		FarRight = 4
	};

	CarStates currentState;

	sf::Vector2f linePosition;

	float velocity;
	float acceleration;
	float distanceFromLine;
};

