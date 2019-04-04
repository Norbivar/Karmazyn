#include "GameEngine.hpp"
#include <ConfigList.hpp>

#include "GameState/GameState_LoadingMenu.hpp"
#include "AssetManager/AssetManager.hpp"
#include "UIManager/UIManager.hpp"
#include "GameStateStack.hpp"

namespace Karmazyn
{
	GameEngine::GameEngine() :
		m_Assets       { std::make_unique<AssetManager>() },
		m_UI           { nullptr },
		m_GameStates   { std::make_unique<GameStateStack>(*this) },
		m_RenderWindow { },

		m_CoreLoopRunning { false }
	{
		m_RenderWindow.create_from_config();
		m_UI = std::make_unique<UIManager>(*this); // needs to be initialized after RenderWindow setup

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
		theLog->info("GameEngine starting!");
		sf::Clock clock;

		m_RenderWindow.createRenderThreadWith(RenderThreadReferencePasser(getUIManager(), getGameStateStack()));

		bool propagnateEvent = false;
		sf::Event polledEvent;

		const float SEC_BETWEEN_TICKS = 1.0f / theConfig->get<float>(Configs::FrameRateCap, 60);
		float diff = 0.0f;

		m_CoreLoopRunning.store(true, std::memory_order::memory_order_relaxed);
		// Main threads main game loop. Application will exit after this.
		while (m_CoreLoopRunning.load(std::memory_order::memory_order_relaxed))
		{
			if (!m_RenderWindow.hasFocus())
			{
				sf::sleep(sf::milliseconds(100));
				continue;
			}

			diff += clock.restart().asSeconds();

			propagnateEvent = m_RenderWindow.pollEvent(polledEvent);

			auto& top = m_GameStates->top();
			if (propagnateEvent)
			{
				if (polledEvent.type == polledEvent.KeyReleased)
				{
					if (polledEvent.key.code == sf::Keyboard::F10)
					{
						theLog->info("f10 pressed!");
						changeScreenSize(1600, 900);
					}
				}
				else top->handleEvent(polledEvent);
			}

			while (diff >= SEC_BETWEEN_TICKS) // if we got a, say: 2 sec freeze, this will make sure we process the skipped ticks
			{
				m_UI->getSystem().injectTimePulse(SEC_BETWEEN_TICKS);
				top->update(SEC_BETWEEN_TICKS);
				diff -= SEC_BETWEEN_TICKS;
			}
		}
		m_RenderWindow.close();
		theLog->info("GameEngine stopping!");
		return 0;
	}
	void GameEngine::Stop()
	{
		m_RenderWindow.close(); // this will close the render window, which will in turn end the main loop and thus the program
		m_CoreLoopRunning.store(false, std::memory_order::memory_order_relaxed);
	}
	void GameEngine::changeScreenSize(const unsigned int newWidth, const unsigned int newHeight)
	{
		float newWidthFloat = 0.0f, newHeightFloat = 0.0f;
		newWidthFloat += newWidth;
		newHeightFloat += newHeight;

		m_RenderWindow.process(RenderWindowCommands::Resize{ newWidth, newHeight });
 		//m_UI->getSystem().notifyDisplaySizeChanged(CEGUI::Sizef{ newWidthFloat, newHeightFloat });
		theLog->info("Screen resolution changed to {}x{} for next restart.", newWidth, newHeight);
	}
	void GameEngine::changeVerticalSynced(bool enabled)
	{
		m_RenderWindow.process(RenderWindowCommands::ToggleVSync(enabled));
	}
}
