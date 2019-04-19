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
	distanceFromLine = 0.0f;
	speedModifier = 1000.0f;
	calculateValues = true;
	givenDistance = 0.0f;
	givenVelocity = 0.0f;

	fuzzyEngine = FisImporter().fromFile("FuzzyCarInferenceSystem2.fis");
}

FuzzyCar::~FuzzyCar()
{
}

void FuzzyCar::Update(float dt)
{
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
	if (calculateValues)
	{
		distanceFromLine = linePosition.x - carSprite.getPosition().x;
		distanceFromLine /= window->getSize().x / 2.0f;
		velocity = distanceFromLine / (dt);
		velocity /= 60.0f;
	}
	else if (!calculateValues)
	{
		if (givenDistance >= -1.0f && givenDistance <= 1.0f && givenVelocity >= -1.0f && givenVelocity <= 1.0f)
		{
			distanceFromLine = givenDistance;
			velocity = givenVelocity;
		}
	}

	// Prevent velocity going outwidth the range in the speed graph
	if (velocity < -1.0f)
	{
		velocity = -1.0f;
	}
	else if (velocity > 1.0f)
	{
		velocity = 1.0f;
	}

	/// Engine usage
	fuzzyEngine->setInputValue("Distance", distanceFromLine);
	fuzzyEngine->setInputValue("Speed", velocity);
	fuzzyEngine->process();
	dir = fuzzyEngine->getOutputValue("Direction");

	if (distanceFromLine < -0.5f && velocity < -0.5f)
	{
		currentState = CarStates::FarLeft;
	}
	if (distanceFromLine > -0.5f && distanceFromLine < -0.1f && velocity > -0.5f && velocity < -0.1f)
	{
		currentState = CarStates::Left;
	}
	if (distanceFromLine > -0.1f && distanceFromLine < 0.1f && velocity > -0.1f && velocity < 0.1f)
	{
		currentState = CarStates::Centre;
	}
	if (distanceFromLine > 0.1f && distanceFromLine < 0.5f && velocity > 0.1f && velocity < 0.5f)
	{
		currentState = CarStates::Right;
	}
	if (distanceFromLine > 0.5f && velocity > 0.5f)
	{
		currentState = CarStates::FarRight;
	}
	
	float moveX = (dir * dt) * speedModifier;

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

	if (carSprite.getPosition().x < 0.0f)
	{
		carSprite.setPosition(sf::Vector2f(0.0f, carSprite.getPosition().y));
	}
	if (carSprite.getPosition().x > window->getSize().x)
	{
		carSprite.setPosition(sf::Vector2f(window->getSize().x, carSprite.getPosition().y));
	}
}

void FuzzyCar::Render()
{
	window->draw(carSprite);
}
