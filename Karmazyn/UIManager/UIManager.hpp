#pragma once

#include <unordered_map>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

namespace Karmazyn
{
	// Translates keyboard and mouse events from their SFML ID to CEGUI used ID.
	class SFMLtoCEGUIInputTranslator
	{
	public:
		SFMLtoCEGUIInputTranslator()
		{
			// EVERY KEY IS CONTAINED IN A VECTOR, PLEASE   !!! ENSURE !!!   THAT KEYS EMPLACED IN THE CONTAINERS ARE THE GOOD ORDER (and fill potential gaps where they exist in SFML)

			// Keys from SFML to CEGUI:
			// m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Unknown, CEGUI::Key::Unknown);// TODO: handle this with the vector-approach
			{
				m_SFKeyToCEGUIKey.reserve(sf::Keyboard::KeyCount); // just to avoid unnecessary reallocations when we easily know the final size

				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::A);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::B);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::C);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::D);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::E);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::F);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::G);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::H);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::I);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::J);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::K);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::L);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::M);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::N);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::O);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::P);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Q);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::R);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::S);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::T);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::U);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::V);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::W);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::X);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Y);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Z);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Zero);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::One);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Two);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Three);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Four);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Five);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Six);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Seven);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Eight);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Nine);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Escape);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::LeftControl);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::LeftShift);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::LeftAlt);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::LeftWindows);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::RightControl);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::RightShift);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::RightAlt);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::RightWindows);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::LeftBracket);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::RightBracket);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Semicolon);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Comma);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Period);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Apostrophe);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Slash);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Backslash);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Grave);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Equals);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Minus);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Space);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Return);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Backspace);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Tab);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::PageUp);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::PageDown);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::End);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Home);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Insert);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Delete);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Add);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Subtract);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Multiply);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Divide);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::ArrowLeft);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::ArrowRight);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::ArrowUp);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::ArrowDown);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Numpad0);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Numpad1);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Numpad2);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Numpad3);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Numpad4);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Numpad5);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Numpad6);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Numpad7);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Numpad8);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Numpad9);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::F1);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::F2);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::F3);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::F4);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::F5);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::F6);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::F7);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::F8);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::F9);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::F10);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::F11);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::F12);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::F13);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::F14);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::F15);
				m_SFKeyToCEGUIKey.emplace_back(CEGUI::Key::Pause);
			}

			// Mouse buttons:
			{
				m_SFMouseButtonToCEGUIMouseButton.reserve(sf::Mouse::ButtonCount);

				m_SFMouseButtonToCEGUIMouseButton.emplace_back(CEGUI::MouseButton::LeftButton);
				m_SFMouseButtonToCEGUIMouseButton.emplace_back(CEGUI::MouseButton::RightButton);
				m_SFMouseButtonToCEGUIMouseButton.emplace_back(CEGUI::MouseButton::MiddleButton);
				m_SFMouseButtonToCEGUIMouseButton.emplace_back(CEGUI::MouseButton::X1Button);
				m_SFMouseButtonToCEGUIMouseButton.emplace_back(CEGUI::MouseButton::X2Button);
			}
		}

		// Returns the corresponding CEGUI key for the given SFML key.
		const CEGUI::Key::Scan& translateKey(const sf::Keyboard::Key& key)
		{
			return m_SFKeyToCEGUIKey[key];
		}

		// Returns the corresponding CEGUI mouse button for the givem SFML mouse button.
		const CEGUI::MouseButton& translateMouse(const sf::Mouse::Button& button)
		{
			return m_SFMouseButtonToCEGUIMouseButton[button];
		}
		
	private:
		// Holds the CEGUI keys in a continious storage. Due to the nature of SFML key declarations, CEGUI keys can be retrieved by indexing the vector with the SFML key ID.
		// Vectors for the above two are possible because the SFML nicely defines keys in an enum, continiously (implicitly), so there will be no gap if the order of their appearance is preserved.
		std::vector<CEGUI::Key::Scan>   m_SFKeyToCEGUIKey;  // much better than unordered_map, as it is continious and cacheable as sh*t
		std::vector<CEGUI::MouseButton> m_SFMouseButtonToCEGUIMouseButton;
	};

	class Engine;

	// Mainly a wrapper around the CEGUI things.
	class UIManager
	{
	public:
		UIManager(Engine& engine);
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

		Engine& theEngine;

		// Responsible for translating the SFML input IDs to CEGUI used ones for injection.
		SFMLtoCEGUIInputTranslator m_InputTranslator;
	};
}