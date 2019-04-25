#include "RenderWindow.hpp"
#include <Logger.hpp>
#include <Config.hpp>

#include "../GameStateMachine.hpp"
#include "../UIManager/UIManager.hpp"
#include "../GameState/IGameState.hpp"

namespace Karmazyn
{
	RenderWindow::RenderWindow() :
		m_WindowStyle(sf::Style::None),
		m_ReferencePasser(nullptr)
	{
		m_ContextSettings.majorVersion = 3;
		m_ContextSettings.minorVersion = 2;
		m_ContextSettings.attributeFlags = sf::ContextSettings::Default;
		m_WindowStyle = theConfig->get<int>(Configs::RenderWindowStyle, sf::Style::None | sf::Style::Fullscreen);
	}
	void RenderWindow::create(unsigned int width, unsigned int height)
	{
		m_RenderWindow.create(
			sf::VideoMode(width, height), "Karmazyn", m_WindowStyle, m_ContextSettings
		);
		theLog->info("Using OpenGL: {}.{}",
			m_RenderWindow.getSettings().majorVersion,
			m_RenderWindow.getSettings().minorVersion
		);
		m_RenderWindow.setVerticalSyncEnabled(theConfig->get<bool>(Configs::VSync, true));
		m_RenderWindow.setMouseCursorVisible(false);
		m_RenderWindow.requestFocus();
	}
	void RenderWindow::create_from_config()
	{
		create(
			theConfig->get<int>(Configs::ResolutionX, 1024), 
			theConfig->get<int>(Configs::ResolutionY, 768)
		);
	}


	void RenderWindow::createRenderThreadWith(const RenderThreadReferencePasser& refpasser) // the refpasser was necessary, as the UI constructor relied on the renderwindow to be created first, and vice versa (for reference)
		// although now that I think of it, I could've easily moved the construction parts of said UI out to an init method instead, but this suffices now
	{
		m_RenderWindow.setActive(false);
		m_RunRenderThread.store(true, std::memory_order::memory_order_relaxed);
		m_RenderThread = std::make_unique<std::thread>([&](RenderThreadReferencePasser passed)
		{
			m_RenderWindow.setActive(true);
			while (m_RunRenderThread.load(std::memory_order::memory_order_relaxed))
			{
				//m_GUI->handleNativeMouseMove(sf::Mouse::getPosition()); // TODO: check whether this is actually better. It feels better a bit, but needs some work around
				m_RenderWindow.clear(sf::Color::White);
				passed.GSM.current().render();
				//passed.UI.draw();
				m_RenderWindow.display();
			}
			m_RenderWindow.setActive(false);
		}, refpasser);
	}
	void RenderWindow::resetRenderThread()
	{
		m_RunRenderThread.store(false, std::memory_order::memory_order_relaxed);
		if (m_RenderThread)
		{
			m_RenderThread->join();
			m_RenderThread.reset(nullptr);
		}
		m_RenderWindow.setActive(true);
	}
}