#include "Engine.hpp"
#include <ConfigList.hpp>

#include "GameState/LoadingMenu/GameState_LoadingMenu.hpp"
#include "AssetManager/AssetManager.hpp"
#include "UIManager/UIManager.hpp"
#include "GameStateMachine.hpp"

namespace Karmazyn
{
	Engine::Engine() :
		m_Assets          { std::make_unique<AssetManager>() },
		m_UI              { nullptr },
		m_GameStateMachine{ std::make_unique<GameStateMachine>(*this) },
		m_RenderWindow { },

		m_CoreLoopRunning { false }
	{
		m_RenderWindow.create_from_config();
		m_UI = std::make_unique<UIManager>(*this); // needs to be initialized after RenderWindow setup

		m_GameStateMachine->transition<GameState_LoadingMenu>();
	}
	Engine::~Engine()
	{

	}
	int Engine::Run()
	{		
		theLog->info("GameEngine starting!");
		sf::Clock clock;

		m_RenderWindow.createRenderThreadWith(RenderThreadReferencePasser(getUIManager(), getGameStateMachine()));

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

			auto& top = m_GameStateMachine->current();
			if (propagnateEvent)
			{
				if (polledEvent.type == polledEvent.Closed)
				{
					Stop();
				}
				else top.handleEvent(polledEvent);
			}

			while (diff >= SEC_BETWEEN_TICKS) // if we got a, say: 2 sec freeze, this will make sure we process the skipped ticks
			{
				m_UI->getSystem().injectTimePulse(SEC_BETWEEN_TICKS);
				top.update(SEC_BETWEEN_TICKS);
				diff -= SEC_BETWEEN_TICKS;
			}
		}
		m_RenderWindow.close();
		theLog->info("GameEngine stopping!");
		return 0;
	}
	void Engine::Stop()
	{
		m_RenderWindow.close(); // this will close the render window, which will in turn end the main loop and thus the program
		m_CoreLoopRunning.store(false, std::memory_order::memory_order_relaxed);
	}
	void Engine::changeScreenSize(const unsigned int newWidth, const unsigned int newHeight)
	{
		float newWidthFloat = 0.0f, newHeightFloat = 0.0f;
		newWidthFloat += newWidth;
		newHeightFloat += newHeight;

		m_RenderWindow.process(RenderWindowCommands::Resize{ newWidth, newHeight });
 		//m_UI->getSystem().notifyDisplaySizeChanged(CEGUI::Sizef{ newWidthFloat, newHeightFloat });
		theLog->info("Screen resolution changed to {}x{} for next restart.", newWidth, newHeight);
	}
	void Engine::changeVerticalSynced(bool enabled)
	{
		m_RenderWindow.process(RenderWindowCommands::ToggleVSync(enabled));
	}
	void Engine::changeWindowedMode(bool enabled)
	{
		m_RenderWindow.process(RenderWindowCommands::ToggleWindowed(enabled));
	}
}
