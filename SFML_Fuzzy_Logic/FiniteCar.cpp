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
	carSprite.setPosition(window->getSize().x / 2.0f, window->getSize().y / 3.0f);

	currentState = CarStates::Centre;

	velocity = 0.0f;
	acceleration = 0.0f;
	distanceFromLine = 0.0f;
	speedModifier = 100000.0f;
}

FiniteCar::~FiniteCar()
{
}

void FiniteCar::Update(float dt)
{
	MoveCar(dt);
}

void FiniteCar::GetLinePosition(sf::Vector2f linePos)
{
	linePosition = linePos;
}

void FiniteCar::MoveCar(float dt)
{
	// Change state of car
	// Depending on distance from line
	// And current speed
	//distanceFromLine = linePosition.x - carSprite.getPosition().x;
	//velocity = distanceFromLine / dt;

	distanceFromLine = linePosition.x - carSprite.getPosition().x;
	distanceFromLine /= window->getSize().x / 2.0f;
	velocity = distanceFromLine / (dt);
	velocity /= 60.0f;

	if (distanceFromLine < -10.0f - carSprite.getTextureRect().width && velocity < -10.0f)
	{
		currentState = CarStates::FarLeft;
		acceleration = 0.15f;
	}
	if (distanceFromLine > -10.0f - carSprite.getTextureRect().width && distanceFromLine < -10.0f && velocity > -10.0f && velocity < -1.0f)
	{
		currentState = CarStates::Left;
		acceleration = 0.075f;
	}
	if (distanceFromLine > -10.0f && distanceFromLine < 10.0f && velocity > -1.0f && velocity < 1.0f)
	{
		currentState = CarStates::Centre;
		acceleration = 0.01f;
	}
	if (distanceFromLine > 10.0f && distanceFromLine < 10.0f + carSprite.getTextureRect().width && velocity > 1.0f && velocity < 10.0f)
	{
		currentState = CarStates::Right;
		acceleration = 0.075f;
	}
	if (distanceFromLine > 10.0f + carSprite.getTextureRect().width && velocity > 10.0f)
	{
		currentState = CarStates::FarRight;
		acceleration = 0.15f;
	}

	float moveX = (velocity * acceleration * dt) * speedModifier;

	switch (currentState)
	{
	case CarStates::FarLeft:
		carSprite.move(sf::Vector2f(moveX, 0.0f));
		break;
	case CarStates::Left:
		carSprite.move(sf::Vector2f(moveX, 0.0f));
		break;
	case CarStates::Centre:
		carSprite.move(sf::Vector2f(moveX, 0.0f));
		break;
	case CarStates::Right:
		carSprite.move(sf::Vector2f(moveX, 0.0f));
		break;
	case CarStates::FarRight:
		carSprite.move(sf::Vector2f(moveX, 0.0f));
		break;
	default:
		break;
	}
}

void FiniteCar::Render()
{
	window->draw(carSprite);
}
