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
}

FiniteCar::~FiniteCar()
{
}

void FiniteCar::Update(float dt)
{

}

void FiniteCar::GetLinePosition(sf::Vector2f linePos)
{
	linePosition = linePos;
}

void FiniteCar::Render()
{
	window->draw(carSprite);
}
