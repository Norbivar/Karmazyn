
#include <Logger.hpp>
#include <ConfigList.hpp>

#include "GameState/GameState_LoadingMenu.hpp"

#include "GameEngine.hpp"

namespace Karmazyn
{
	GameEngine::GameEngine() :
		m_Config(ConfigSettings::cConfigFilesToReadInOrder)
	{
		sf::ContextSettings contextSettings;

		m_RenderWindow.create(
			sf::VideoMode(
				m_Config.get<int>(Configs::Root_Graphics, Configs::Graphics_Render_X, 1024), 
				m_Config.get<int>(Configs::Root_Graphics, Configs::Graphics_Render_Y, 768)
			),
			"Karmazyn", 
			sf::Style::None,
			contextSettings
		); // TODO: set style to sf::Style::Fullscreen | sf::Style::None when fitting

		m_RenderWindow.setFramerateLimit(
			m_Config.get<int>(Configs::Root_Graphics, Configs::Graphics_Frame_Cap, 60)
		);

		m_GameStates.emplace(
			std::make_unique<GameState_LoadingMenu>(*this)
		);
	}
	int GameEngine::Run()
	{
		theLog->info("GameEngine starting!");
		sf::Clock clock;

		m_RenderWindow.setActive(false);
		m_RenderThread = std::make_unique<std::thread>([&]()
		{
			while (m_RunRenderThread.load(std::memory_order::memory_order_relaxed)) // this should be just optimal 
			{
				m_RenderWindow.clear(sf::Color::Black);
				m_GameStates.top()->render();
				m_RenderWindow.display();
			}
		});

		bool propagnateEvent = false;
		sf::Event polledEvent;

		const float MS_PER_UPDATE = 1000.0f / m_Config.get<int>(Configs::Root_Graphics, Configs::Graphics_Frame_Cap, 60);
		float diff = 0.0f;

		while (m_RenderWindow.isOpen())
		{
			diff += clock.restart().asSeconds();

			propagnateEvent = m_RenderWindow.pollEvent(polledEvent);
			if (polledEvent.type == sf::Event::Closed)
				m_RenderWindow.close();

			auto& top = m_GameStates.top();
			if (propagnateEvent)
				top->handleEvent(polledEvent);
			
			while (diff >= MS_PER_UPDATE) // if we got a, say: 2 sec freeze, this will make sure we process the skipped ticks
			{
				top->update(diff);
				diff -= MS_PER_UPDATE;
			}
		}
		return 0;
	}
	void GameEngine::Stop()
	{
		m_RunRenderThread.store(false, std::memory_order::memory_order_relaxed);
		m_RenderThread->join();
		m_RenderThread.reset();

		m_RenderWindow.close();
	}
}
