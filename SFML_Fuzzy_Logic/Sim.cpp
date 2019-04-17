#include "Sim.h"

Sim::Sim(sf::RenderWindow* hwnd, Input* in)
{
	// Set window and input for the simulation
	window = hwnd;
	input = in;

	// Set up the racing line
	racingLine = new RacingLine(hwnd, in, sf::Vector2f(5.0f, window->getSize().y), sf::Vector2f(window->getSize().x / 2.0f, 0.0f), 1000.0f);

	// Set up the finite state machine car
	finiteCar = new FiniteCar(hwnd);

	// Set up the fuzzy logic car
	fuzzyCar = new FuzzyCar(hwnd);
}

Sim::~Sim()
{
}

void Sim::update(float dt)
{
	// Update the racing line
	racingLine->Update(dt);

	// Give the lines position to the finite state machine car
	finiteCar->GetLinePosition(racingLine->GetPosition());

	// Give the lines position to the fuzzy logic car
	fuzzyCar->GetLinePosition(racingLine->GetPosition());

	// Update the finite state machine car
	finiteCar->Update(dt);

	// Update the fuzzy logic car
	fuzzyCar->Update(dt);
}

void Sim::gui(float dt)
{
	sf::Time t = sf::seconds(dt);
	ImGui::SFML::Update(*window, t);

	// Begin ImGui Window
	ImGui::Begin("Debug");

	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

	if (ImGui::CollapsingHeader("Finite Car"))
	{
		ImGui::Image(finiteCar->getSprite());
		ImGui::Text("Velocity: %.1f", finiteCar->getVelocity());
		ImGui::Text("Distance from line: %.1f", finiteCar->getDistanceFromLine());
		ImGui::Text("Speed Modifier");
		ImGui::InputFloat("", &finiteCar->getSpeedModifier());
	}

	if (ImGui::CollapsingHeader("Fuzzy Car"))
	{
		ImGui::Image(fuzzyCar->getSprite());
		ImGui::Text("Direction: %.1f", fuzzyCar->getDirection());
		ImGui::Text("Velocity: %.1f", fuzzyCar->getVelocity());
		ImGui::Text("Distance from line: %.1f", fuzzyCar->getDistanceFromLine());
		ImGui::Text("Speed Modifier");
		ImGui::InputFloat("",&fuzzyCar->getSpeedModifier());
	}

	// End ImGui Window
	ImGui::End();

	ImGui::SFML::Render(*window);
}

void Sim::render(float dt)
{
	beginDraw();

	// Draw the racing line
	racingLine->Render();

	// Draw the finite state machine car
	finiteCar->Render();

	// Draw the fuzzy logic car
	fuzzyCar->Render();

	gui(dt);

	endDraw();
}

void Sim::beginDraw()
{
	// Set window colour to black when clearing
	window->clear(sf::Color::Black);
}

void Sim::endDraw()
{
	window->display();
}