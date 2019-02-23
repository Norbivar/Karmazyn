
#include <Logger.hpp>
#include <ConfigList.hpp>

#include "GameState/IGameState.hpp"
#include "GameState/GameStateMenu.hpp"

#include "Application.hpp"

namespace Karmazyn
{
	Application::Application() :
		m_Config(ConfigSettings::cConfigFilesToReadInOrder)
	{
		m_RenderWindow.create(sf::VideoMode(
			m_Config.get<int>(Configs::Root_Graphics, Configs::Graphics_Render_X, 1024), 
			m_Config.get<int>(Configs::Root_Graphics, Configs::Graphics_Render_Y, 768)
		), "Karmazyn"); 

		m_RenderWindow.setFramerateLimit(
			m_Config.get<int>(Configs::Root_Graphics, Configs::Graphics_Frame_Cap, 60)
		);

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

			//top->update(diff);
			//top->handleInput();
			//top->render();
		}
		return 0;
	}
}
