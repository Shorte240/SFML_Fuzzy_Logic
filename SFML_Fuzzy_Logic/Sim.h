// State to manage the simulation.

#pragma once

#include "Input.h"
#include "RacingLine.h"
#include "FiniteCar.h"
#include "FuzzyCar.h"
#include <imgui.h>
#include <imgui-sfml/imgui-SFML.h>

class Sim
{
public:
	Sim(sf::RenderWindow* hwnd, Input *input);
	~Sim();

	// Functions
	void update(float dt);
	void gui(float dt);
	void render(float dt);

private:
	// Background setup
	sf::RenderWindow* window;
	Input* input;

	// Simulation elements
	RacingLine* racingLine;
	FiniteCar* finiteCar;
	FuzzyCar* fuzzyCar;
	
	// Draw functions
	void beginDraw();
	void endDraw();
};