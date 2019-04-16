#include "FiniteCar.h"

FiniteCar::FiniteCar(sf::RenderWindow* hwnd)
{
	window = hwnd;

	if (!carTexture.loadFromFile("textures/redCar.png"))
	{
		// error...
	}
	carTexture.setSmooth(true);
	carSprite.setTexture(carTexture);
	carSprite.setScale(sf::Vector2f(0.25f, 0.25f));
	carSprite.setOrigin(sf::Vector2f(carTexture.getSize().x / 2.0f, carTexture.getSize().y / 2.0f));
	carSprite.setPosition(window->getSize().x / 2.0f, window->getSize().y / 2.0f);

	currentState = CarStates::Centre;
}

FiniteCar::~FiniteCar()
{
}

void FiniteCar::Update(float dt)
{
	MoveCar();
}

void FiniteCar::GetLinePosition(sf::Vector2f linePos)
{
	linePosition = linePos;
}

void FiniteCar::MoveCar()
{
	// Change state of car
	// Depending on distance from line
	// And current speed
	if (linePosition.x < carSprite.getPosition().x)
	{
		currentState = CarStates::Left;
	}
	if (linePosition.x == carSprite.getPosition().x)
	{
		currentState = CarStates::Centre;
	}
	if (linePosition.x > carSprite.getPosition().x)
	{
		currentState = CarStates::Right;
	}
}

void FiniteCar::Render()
{
	window->draw(carSprite);
}
