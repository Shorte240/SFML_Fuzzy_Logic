#include "FuzzyCar.h"

FuzzyCar::FuzzyCar(sf::RenderWindow* hwnd)
{
	window = hwnd;

	if (!carTexture.loadFromFile("textures/greenCar.png"))
	{
		// error...
	}
	carTexture.setSmooth(true);
	carSprite.setTexture(carTexture);
	carSprite.setScale(sf::Vector2f(0.25f, 0.25f));
	carSprite.setOrigin(sf::Vector2f(carTexture.getSize().x / 2.0f, carTexture.getSize().y / 2.0f));
	carSprite.setPosition(window->getSize().x / 2.0f, window->getSize().y / 1.5f);

	currentState = CarStates::Centre;

	velocity = 0.0f;
	acceleration = 0.0f;
	distanceFromLine = 0.0f;
	speedModifier = 1000.0f;

	fuzzyEngine = FisImporter().fromFile("FuzzyCarInferenceSystem.fis");
}

FuzzyCar::~FuzzyCar()
{
}

void FuzzyCar::Update(float dt)
{
	distanceFromLine = linePosition.x - carSprite.getPosition().x;
	distanceFromLine /= window->getSize().x / 2.0f;
	velocity = distanceFromLine / (dt);
	velocity /= 60.0f;

	/// Engine usage
	fuzzyEngine->setInputValue("Distance", distanceFromLine);
	fuzzyEngine->setInputValue("Speed", velocity);
	fuzzyEngine->process();
	dir = fuzzyEngine->getOutputValue("Direction");

	MoveCar(dt);
}

void FuzzyCar::GetLinePosition(sf::Vector2f linePos)
{
	linePosition = linePos;
}

void FuzzyCar::MoveCar(float dt)
{
	// Change state of car
	// Depending on distance from line
	// And current speed

	if (distanceFromLine < -0.5f && velocity < -0.5f)
	{
		currentState = CarStates::FarLeft;
		acceleration = 0.15f;
	}
	if (distanceFromLine > -0.5f && distanceFromLine < -0.1f && velocity > -0.5f && velocity < -0.1f)
	{
		currentState = CarStates::Left;
		acceleration = 0.075f;
	}
	if (distanceFromLine > -0.1f && distanceFromLine < 0.1f && velocity > -0.1f && velocity < 0.1f)
	{
		currentState = CarStates::Centre;
		acceleration = 0.01f;
	}
	if (distanceFromLine > 0.1f && distanceFromLine < 0.5f && velocity > 0.1f && velocity < 0.5f)
	{
		currentState = CarStates::Right;
		acceleration = 0.075f;
	}
	if (distanceFromLine > 0.5f && velocity > 0.5f)
	{
		currentState = CarStates::FarRight;
		acceleration = 0.15f;
	}

	/*switch (currentState)
	{
	case CarStates::FarLeft:
		carSprite.move(sf::Vector2f(velocity * acceleration * dt * speedModifier, 0.0f));
		break;
	case CarStates::Left:
		carSprite.move(sf::Vector2f(velocity * acceleration * dt* speedModifier, 0.0f));
		break;
	case CarStates::Centre:
		carSprite.move(sf::Vector2f(velocity * acceleration * dt* speedModifier, 0.0f));
		break;
	case CarStates::Right:
		carSprite.move(sf::Vector2f(velocity * acceleration * dt* speedModifier, 0.0f));
		break;
	case CarStates::FarRight:
		carSprite.move(sf::Vector2f(velocity * acceleration * dt* speedModifier, 0.0f));
		break;
	default:
		break;
	}*/

	switch (currentState)
	{
	case CarStates::FarLeft:
		carSprite.move(sf::Vector2f(dir * dt * speedModifier, 0.0f));
		break;
	case CarStates::Left:
		carSprite.move(sf::Vector2f(dir * dt* speedModifier, 0.0f));
		break;
	case CarStates::Centre:
		carSprite.move(sf::Vector2f(dir * dt* speedModifier, 0.0f));
		break;
	case CarStates::Right:
		carSprite.move(sf::Vector2f(dir * dt* speedModifier, 0.0f));
		break;
	case CarStates::FarRight:
		carSprite.move(sf::Vector2f(dir * dt* speedModifier, 0.0f));
		break;
	default:
		break;
	}
}

void FuzzyCar::Render()
{
	window->draw(carSprite);
}
