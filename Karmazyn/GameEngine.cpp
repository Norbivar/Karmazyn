
#include <Logger.hpp>
#include <ConfigList.hpp>

#include "GameState/GameState_LoadingMenu.hpp"

#include "GameEngine.hpp"

namespace Karmazyn
{
	GameEngine::GameEngine() :
		m_Config(ConfigSettings::cConfigFilesToReadInOrder)
	{
		m_RenderWindow.create(
			sf::VideoMode(
				m_Config.get<int>(Configs::Root_Graphics, Configs::Graphics_Render_X, 1024), 
				m_Config.get<int>(Configs::Root_Graphics, Configs::Graphics_Render_Y, 768)
			),
			"Karmazyn", 
			sf::Style::None
		); // TODO: set style to sf::Style::Fullscreen | sf::Style::None when fitting

		m_RenderWindow.setFramerateLimit(
			m_Config.get<int>(Configs::Root_Graphics, Configs::Graphics_Frame_Cap, 60)
		);
		m_GameStates.emplace(new GameState_LoadingMenu(*this));
	}
	int GameEngine::Run()
	{
		theLog->info("GameEngine starting!");
		sf::Clock clock;

		m_RenderWindow.setActive(false);
		m_RenderThread = std::make_unique<std::thread>([&]()
		{
			while (true)
			{
				m_RenderWindow.clear(sf::Color::Black);
				m_GameStates.top()->render();
				m_RenderWindow.display();
			}
		});

		bool propagnateEvent = false;
		sf::Event polledEvent;
		while (m_RenderWindow.isOpen())
		{
			const auto diff = clock.restart().asSeconds();

			propagnateEvent = m_RenderWindow.pollEvent(polledEvent);
			if (polledEvent.type == sf::Event::Closed)
				m_RenderWindow.close();

			auto& top = m_GameStates.top();
			if (propagnateEvent)
				top->handleEvent(polledEvent);
			
			top->update(diff);
		}
		return 0;
	}
}
