#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-sfml\imgui-SFML.h>
#include "Input.h"
#include "Sim.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "");
	window.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(window);


	//For Delta Time
	sf::Clock clock;
	float deltaTime;

	Input input;
	Sim sim(&window, &input);

	sf::Color bgColor;

	float color[3] = { 0.f, 0.f, 0.f };

	// let's use char array as buffer, see next part
	// for instructions on using std::string with ImGui
	char windowTitle[255] = "ImGui + SFML = <3";

	window.setTitle(windowTitle);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
				break;
			case sf::Event::KeyPressed:
				//update input class
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//update input class
				input.setKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				//update input class
				input.setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseLeftDown(true);
				}
				else if (event.mouseButton.button == sf::Mouse::Middle)
				{
					//update input class
					input.setMouseMiddleDown(true);
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					//update input class
					input.setMouseRightDown(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseLeftDown(false);
				}
				else if (event.mouseButton.button == sf::Mouse::Middle)
				{
					//update input class
					input.setMouseMiddleDown(false);
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					//update input class
					input.setMouseRightDown(false);
				}
				break;
			default:
				// don't handle other events
				break;
			}
		}

		if (input.isKeyDown(sf::Keyboard::Escape))
		{
			input.setKeyUp(sf::Keyboard::Escape);
			window.close();
		}

		//Calculate delta time. How much time has passed
		//since it was last calculated (in seconds) and restart the clock.
		deltaTime = clock.restart().asSeconds();

		

		sim.update(deltaTime);
		sim.render(deltaTime);
	}
	ImGui::SFML::Shutdown();
}