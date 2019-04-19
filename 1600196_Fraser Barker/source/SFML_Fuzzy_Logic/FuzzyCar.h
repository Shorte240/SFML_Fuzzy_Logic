#pragma once

#include <SFML/Graphics.hpp>
#include "fl\Headers.h"

using namespace fl;

class FuzzyCar
{
public:
	FuzzyCar(sf::RenderWindow* hwnd);
	~FuzzyCar();

	void Update(float dt);
	void GetLinePosition(sf::Vector2f linePos);
	void MoveCar(float dt);
	void Render();
	float getDirection() { return dir; };
	float getVelocity() { return velocity; };
	float getDistanceFromLine() { return distanceFromLine; };
	float& getSpeedModifier() { return speedModifier; };
	bool& getCalculateValues() { return calculateValues; };
	float& getGivenVelocity() { return givenVelocity; };
	float& getGivenDistance() { return givenDistance; };
	sf::Sprite getSprite() { return carSprite; };

private:
	sf::RenderWindow* window;

	Engine* fuzzyEngine;

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
	float distanceFromLine;
	float dir;
	float speedModifier;
	bool calculateValues;
	float givenVelocity;
	float givenDistance;
};

