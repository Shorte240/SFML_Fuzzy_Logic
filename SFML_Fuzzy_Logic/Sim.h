// State to manage the simulation.

#pragma once

#include "Input.h"
#include "RacingLine.h"
#include "FiniteCar.h"
#include <imgui.h>
#include <imgui-sfml/imgui-SFML.h>

class Sim
{
public:
	Sim(sf::RenderWindow* hwnd, Input *input, sf::Clock* clock);
	~Sim();

	// Functions
	void update(float dt);
	void gui(float dt);
	void render(float dt);
	void reset();

private:
	// Background setup
	sf::RenderWindow* window;
	Input* input;

	// Functions
	void updateText();

	// Simulation elements
	RacingLine* racingLine;
	FiniteCar* finiteCar;

	// Text setup
	sf::Font font;
	int fps;
	sf::Text fpsText;

	sf::Clock* cl;

	// Draw functions
	void beginDraw();
	void endDraw();
};