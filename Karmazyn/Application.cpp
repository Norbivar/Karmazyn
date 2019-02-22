
#include <Logger.h>
#include "GameState/IGameState.hpp"
#include "GameState/GameStateMenu.hpp"

#include "Application.hpp"

namespace Karmazyn
{
	Application::Application()
	{
		m_RenderWindow.create(sf::VideoMode(1024, 768), "Karmazyn"); // TODO: refactor to use a config-usable render size
		m_RenderWindow.setFramerateLimit(60); // TODO: refactor to use config-usable frame limit

		m_GameStateStack.emplace(new GameState_Menu(this));
	}
	int Application::Run()
	{
		theLog->info("Application starting!");
		sf::Clock clock;

		while (m_RenderWindow.isOpen())
		{
			const auto diff = clock.restart().asMilliseconds();
			const auto& top = m_GameStateStack.top();

			top->update(diff);
			top->handleInput();
			top->render();
		}
		return 0;
	}
}
