#include "GameEngine.hpp"
#include <ConfigList.hpp>

#include "GameState/GameState_LoadingMenu.hpp"
#include "AssetManager/AssetManager.hpp"
#include "GUIManager/GUIManager.hpp"
#include "GameStateStack.hpp"

namespace Karmazyn
{
	GameEngine::GameEngine() :
		m_GUI        { nullptr },

		m_IsRunning  { false },
		m_Assets     { std::make_unique<AssetManager>() },
		m_GameStates { std::make_unique<GameStateStack>(*this) },
		m_Config     { ConfigSettings::cConfigFilesToReadInOrder }
	{
		sf::ContextSettings contextSettings;
		contextSettings.majorVersion = 2;
		contextSettings.minorVersion = 8;
		theLog->info("Using OpenGL: {}.{}", contextSettings.majorVersion, contextSettings.minorVersion);
		
		int windowStyle = m_Config.get<int>(Configs::RenderWindowStyle, sf::Style::None | sf::Style::Fullscreen);

		m_RenderWindow.create(
			sf::VideoMode(
				m_Config.get<int>(Configs::ResolutionX, 1024),
				m_Config.get<int>(Configs::ResolutionY, 768)
			),
			"Karmazyn", windowStyle, contextSettings
		); 

		m_RenderWindow.setMouseCursorVisible(false);
		m_RenderWindow.setVerticalSyncEnabled(m_Config.get<bool>(Configs::VSync, false));
		m_RenderWindow.setFramerateLimit(m_Config.get<int>(Configs::FrameRateCap, 60));
		m_RenderWindow.requestFocus();

		m_GUI = std::make_unique<GUIManager>(*this); // needs to be initialized after RenderWindow setup

		// consider abstracting this out, to reduce GameEngine dependency hell:
		// Move gamestatestack out to it's own class, create functions for pushing/poping gamestates into it through predefined strings(?)
		// like "LoadingMenu" -> GameState_LoadingMenu
		// But this should be compile time checked (for invalid strings) and done
		m_GameStates->push(
			std::make_unique<GameState_LoadingMenu>(*this)
		);
	}
	GameEngine::~GameEngine()
	{

	}
	int GameEngine::Run()
	{
		if (m_IsRunning)
		{
			theLog->warn("GameEngine Run() was called while it was already running!");
			return 1;
		}
		m_IsRunning = true;
			
		theLog->info("GameEngine starting!");
		sf::Clock clock;

		m_RenderWindow.setActive(false);
		m_RenderThread = std::make_unique<std::thread>([&]()
		{
			while (m_RunRenderThread.load(std::memory_order::memory_order_relaxed)) // this should be just optimal 
			{
				//m_GUI->handleNativeMouseMove(sf::Mouse::getPosition()); // TODO: check whether this is actually better. It feels better a bit, but needs some work around
				m_RenderWindow.clear(sf::Color::Black);
				m_GameStates->top()->render();
				m_RenderWindow.display();
			}
		});

		bool propagnateEvent = false;
		sf::Event polledEvent;

		const float SEC_BETWEEN_TICKS = 1.0f / m_Config.get<float>(Configs::FrameRateCap, 60);
		float diff = 0.0f;

		// Main threads main game loop. Application will exit after this.
		while (m_RenderWindow.isOpen())
		{
			if (!m_RenderWindow.hasFocus())
			{
				sf::sleep(sf::milliseconds(100));
				continue;
			}

			diff += clock.restart().asSeconds();

			propagnateEvent = m_RenderWindow.pollEvent(polledEvent);
			if (polledEvent.type == sf::Event::Closed)
				m_RenderWindow.close();

			auto& top = m_GameStates->top();
			if (propagnateEvent)
			{
				top->handleEvent(polledEvent);
			}
			m_GUI->getSystem().injectTimePulse(diff);

			while (diff >= SEC_BETWEEN_TICKS) // if we got a, say: 2 sec freeze, this will make sure we process the skipped ticks
			{
				top->update(SEC_BETWEEN_TICKS);
				diff -= SEC_BETWEEN_TICKS;
			}
		}
		theLog->info("GameEngine stopping!");
		return 0;
	}
	void GameEngine::Stop()
	{
		if (m_IsRunning)
		{
			m_RunRenderThread.store(false, std::memory_order::memory_order_relaxed);
			m_RenderThread->join();
			m_RenderThread.reset();
			m_IsRunning = false;

			m_RenderWindow.close();
		}
		else theLog->warn("GameEngine Stop() was called while not running!");
	}
}
