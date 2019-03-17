#pragma once

#include <unordered_map>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GLRenderer.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

namespace Karmazyn
{
	class GameEngine;

	// Mainly a wrapper around the CEGUI things.
	class GUIManager
	{
	public:
		GUIManager(GameEngine& engine);
		~GUIManager() = default;

		GUIManager(const GUIManager&) = delete;
		GUIManager(GUIManager&&) = delete;

		GUIManager& operator=(const GUIManager&) = delete;
		GUIManager& operator=(GUIManager&&) = delete;

		CEGUI::WindowManager& getWindowManager() { return m_WindowManager; }
		// Renders all active Windows.
		void draw() const { m_System.renderAllGUIContexts(); }
		// Returns a reference to the singleton object CEGUI::System.
		// Also a shortcut for 'CEGUI::System::getSingletonPtr()'
		CEGUI::System& getSystem() { return m_System; }

		//Application& getApplication() { return rApplication; }

		// Gets an Event from SFML and processes it.
		// If an EVENT needs to be handled at both places (GUIManager.cpp + Application.cpp), then the handler needs to return FALSE.
		// Whenever the handler returns TRUE it means that the Application ignores it.
		bool handleEvent(const sf::Event& ev);

		void handleNativeMouseMove(const sf::Vector2i& ev);

	private:
		// Non-owning pointers to assets.
		//sf::RenderWindow&		pMyWindow;

		CEGUI::OpenGLRenderer&  m_Renderer;
		CEGUI::System&          m_System;
		CEGUI::WindowManager&   m_WindowManager;

		//std::unique_ptr<GUI_MainMenuHandler> pMyMainMenu;

		GameEngine& theEngine;

		// Given an 'sf::Mouse::Button', returns the corresponding CEGUI::MouseButton upon searching.
		std::unordered_map<sf::Mouse::Button, CEGUI::MouseButton> m_MouseInputTranslator;
	};
}