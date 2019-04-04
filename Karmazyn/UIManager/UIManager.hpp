#pragma once

#include <unordered_map>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

#include <atomic>

namespace Karmazyn
{
	class GameEngine;

	// Mainly a wrapper around the CEGUI things.
	class UIManager
	{
	public:
		UIManager(GameEngine& engine);
		~UIManager() = default;

		UIManager(const UIManager&) = delete;
		UIManager(UIManager&&) = delete;

		UIManager& operator=(const UIManager&) = delete;
		UIManager& operator=(UIManager&&) = delete;

		CEGUI::WindowManager& getWindowManager() { return m_WindowManager; }

		// Renders all active Windows.
		void draw() const { m_System.renderAllGUIContexts(); }

		void destroyWindow(CEGUI::Window* win) { m_WindowManager.destroyWindow(win); }

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
		CEGUI::OpenGL3Renderer& m_Renderer;
		CEGUI::System&          m_System;
		CEGUI::WindowManager&   m_WindowManager;

		GameEngine& theEngine;

		// Given an 'sf::Mouse::Button', returns the corresponding CEGUI::MouseButton upon searching.
		std::unordered_map<sf::Mouse::Button, CEGUI::MouseButton> m_MouseInputTranslator;
	};
}