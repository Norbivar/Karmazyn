
#include <Logger.h>

#include "Application.hpp"

namespace Karmazyn
{
	Application::Application()
	{
		m_RenderWindow.create(sf::VideoMode(800, 600), "City Builder"); // TODO: refactor to use a config-usable render size
		m_RenderWindow.setFramerateLimit(60); // TODO: refactor to use config-usable frame limit
	}
	int Application::Run()
	{
		theLog->info("Application starting.");
		sf::Clock clock;

		while (m_RenderWindow.isOpen())
		{
			const auto dt = clock.restart().asMilliseconds();

		}
		return 0;
	}
}
