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
	float getVelocity() { return velocity; };
	float getDistanceFromLine() { return distanceFromLine; };
	float& getSpeedModifier() { return speedModifier; };
	sf::Sprite getSprite() { return carSprite; };

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
	float speedModifier;
};

