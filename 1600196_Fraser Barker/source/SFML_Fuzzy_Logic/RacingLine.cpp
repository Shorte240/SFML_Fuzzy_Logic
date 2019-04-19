#include "RacingLine.h"

RacingLine::RacingLine(sf::RenderWindow* hwnd, Input* in, sf::Vector2f size, sf::Vector2f pos, float speed)
{
	window = hwnd;
	input = in;
	line.setSize(size);
	line.setOrigin(sf::Vector2f(size.x / 2.0f, 0.0f));
	line.setPosition(pos);
	movementSpeed = speed;
}

RacingLine::~RacingLine()
{
}

void RacingLine::Update(float dt)
{
	HandleInput(dt);
}

void RacingLine::HandleInput(float dt)
{
	// Move line left
	if (input->isKeyDown(sf::Keyboard::A) || input->isKeyDown(sf::Keyboard::Left))
	{
		// Ensure the line doesn't exceed the left bound
		if (line.getPosition().x > 10.0f)
		{
			// Move the line 1 unit left
			line.move(sf::Vector2f(-movementSpeed * dt, 0.0f));
		}
	}

	// Move line right
	if (input->isKeyDown(sf::Keyboard::D) || input->isKeyDown(sf::Keyboard::Right))
	{
		// Ensure the line doesn't exceed the right bound
		if (line.getPosition().x < window->getSize().x - line.getSize().x)
		{
			// Move the line 1 unit right
			line.move(sf::Vector2f(movementSpeed * dt, 0.0f));
		}
	}
}

void RacingLine::Render()
{
	// Render the racing line
	window->draw(line);
}
