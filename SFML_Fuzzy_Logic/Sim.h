// State to manage the simulation.

#pragma once

#include "Input.h"
#include "RacingLine.h"
#include "FiniteCar.h"
#include "FuzzyCar.h"
#include <imgui.h>
#include <imgui-sfml/imgui-SFML.h>
#include <chrono>
#include <fstream>

// Import things we need from the standard library
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::ofstream;

// Define the alias "the_clock" for the clock type we're going to use.
typedef std::chrono::steady_clock the_serial_clock;

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

	// Timing variables
	ofstream application_timings_file;
	
	// Draw functions
	void beginDraw();
	void endDraw();
};