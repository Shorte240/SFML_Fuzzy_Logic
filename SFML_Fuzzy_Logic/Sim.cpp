#include "Sim.h"

Sim::Sim(sf::RenderWindow* hwnd, Input* in)
{
	// Set window and input for the simulation
	window = hwnd;
	input = in;

	// Initial fps value
	fps = 0.0f;

	// Set up the racing line
	racingLine = new RacingLine(hwnd, in, sf::Vector2f(5.0f, window->getSize().y), sf::Vector2f(window->getSize().x / 2.0f, 0.0f), 1000.0f);

	// Set up the finite state machine car
	finiteCar = new FiniteCar(hwnd);

	// Set up font
	if (!font.loadFromFile("font/arial.ttf"))
	{
		printf("Font can't load\n");
	}

	fuzzyEngine = FisImporter().fromFile("FuzzyCarInferenceSystem.fis");
}

Sim::~Sim()
{
}

void Sim::update(float dt)
{
	// Calculate FPS
	fps = 1.0f / dt;

	// Update the racing line
	racingLine->Update(dt);

	// Give the lines position to the finite state machine car
	finiteCar->GetLinePosition(racingLine->GetPosition());

	// Engine usage
	//fuzzyEngine->setInputVariable()
	//fuzzyEngine->process()
	//float output = fuzzyEngine->getOutputVariable();

	// Update the finite state machine car
	finiteCar->Update(dt);

	// Update all the text variables
	updateText();
}

void Sim::gui(float dt)
{
	sf::Time t = sf::seconds(dt);
	ImGui::SFML::Update(*window, t);

	ImGui::Begin("Sample window"); // begin window

	//							   // Background color edit
	////if (ImGui::ColorEdit3("Background color", color)) {
	////	// this code gets called if color value changes, so
	////	// the background color is upgraded automatically!
	////	bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
	////	bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
	////	bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
	////}

	//// Window title text edit
	////ImGui::InputText("Window title", windowTitle, 255);

	////if (ImGui::Button("Update window title")) {
	////	// this code gets if user clicks on the button
	////	// yes, you could have written if(ImGui::InputText(...))
	////	// but I do this to show how buttons work :)
	////	window.setTitle(windowTitle);
	////}
	ImGui::End(); // end window

	ImGui::SFML::Render(*window);

}

void Sim::render(float dt)
{
	beginDraw();

	// Draw FPS text
	window->draw(fpsText);

	// Draw the racing line
	racingLine->Render();

	// Draw the finite state machine car
	finiteCar->Render();

	gui(dt);

	endDraw();
}

void Sim::reset()
{
}

void Sim::updateText()
{
	// FPS text
	fpsText.setFont(font);
	fpsText.setCharacterSize(12);
	fpsText.setString("FPS: " + std::to_string(fps));
	fpsText.setFillColor(sf::Color::White);
	fpsText.setPosition(window->getSize().x - 162, 0);
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