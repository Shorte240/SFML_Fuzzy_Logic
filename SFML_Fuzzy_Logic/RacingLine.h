#pragma once

#include "Input.h"

class RacingLine
{
public:
	RacingLine(sf::RenderWindow* hwnd, Input* in, sf::Vector2f size, sf::Vector2f pos, float speed);
	~RacingLine();

	void Update(float dt);
	void HandleInput(float dt);
	sf::Vector2f GetPosition() { return line.getPosition(); };
	void Render();

private:
	sf::RenderWindow* window;
	Input* input;
	sf::RectangleShape line;
	float movementSpeed;
};

