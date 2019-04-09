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
			// Mouse buttons:
			m_mapSFMouseButtonToCEGUIMouseButton.emplace(sf::Mouse::Button::Left,     CEGUI::MouseButton::LeftButton);
			m_mapSFMouseButtonToCEGUIMouseButton.emplace(sf::Mouse::Button::Right,    CEGUI::MouseButton::RightButton);
			m_mapSFMouseButtonToCEGUIMouseButton.emplace(sf::Mouse::Button::Middle,   CEGUI::MouseButton::MiddleButton);
			m_mapSFMouseButtonToCEGUIMouseButton.emplace(sf::Mouse::Button::XButton1, CEGUI::MouseButton::X1Button);
			m_mapSFMouseButtonToCEGUIMouseButton.emplace(sf::Mouse::Button::XButton2, CEGUI::MouseButton::X2Button);

			// Keys:
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Unknown, CEGUI::Key::Unknown);

			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::A, CEGUI::Key::A);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::B, CEGUI::Key::B);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::C, CEGUI::Key::C);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::D, CEGUI::Key::D);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::E, CEGUI::Key::E);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::F, CEGUI::Key::F);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::G, CEGUI::Key::G);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::H, CEGUI::Key::H);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::I, CEGUI::Key::I);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::J, CEGUI::Key::J);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::K, CEGUI::Key::K);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::L, CEGUI::Key::L);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::M, CEGUI::Key::M);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::N, CEGUI::Key::N);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::O, CEGUI::Key::O);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::P, CEGUI::Key::P);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Q, CEGUI::Key::Q);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::R, CEGUI::Key::R);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::S, CEGUI::Key::S);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::T, CEGUI::Key::T);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::U, CEGUI::Key::U);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::V, CEGUI::Key::V);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::W, CEGUI::Key::W);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::X, CEGUI::Key::X);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Y, CEGUI::Key::Y);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Z, CEGUI::Key::Z);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Num0, CEGUI::Key::Zero);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Num1, CEGUI::Key::One);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Num2, CEGUI::Key::Two);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Num3, CEGUI::Key::Three);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Num4, CEGUI::Key::Four);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Num5, CEGUI::Key::Five);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Num6, CEGUI::Key::Six);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Num7, CEGUI::Key::Seven);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Num8, CEGUI::Key::Eight);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Num9, CEGUI::Key::Nine);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Escape, CEGUI::Key::Escape);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::LControl, CEGUI::Key::LeftControl);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::LShift, CEGUI::Key::LeftShift);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::LAlt, CEGUI::Key::LeftAlt);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::LSystem, CEGUI::Key::LeftWindows);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::RControl, CEGUI::Key::RightControl);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::RShift, CEGUI::Key::RightShift);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::RAlt, CEGUI::Key::RightAlt);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::RSystem, CEGUI::Key::RightWindows);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::LBracket, CEGUI::Key::LeftBracket);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::RBracket, CEGUI::Key::RightBracket);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::SemiColon, CEGUI::Key::Semicolon);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Comma, CEGUI::Key::Comma);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Period, CEGUI::Key::Period);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Quote, CEGUI::Key::Apostrophe);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Slash, CEGUI::Key::Slash);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::BackSlash, CEGUI::Key::Backslash);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Tilde, CEGUI::Key::Grave);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Equal, CEGUI::Key::Equals);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Dash, CEGUI::Key::Minus);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Space, CEGUI::Key::Space);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Return, CEGUI::Key::Return);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::BackSpace, CEGUI::Key::Backspace);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Tab, CEGUI::Key::Tab);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::PageUp, CEGUI::Key::PageUp);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::PageDown, CEGUI::Key::PageDown);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::End, CEGUI::Key::End);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Home, CEGUI::Key::Home);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Insert, CEGUI::Key::Insert);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Delete, CEGUI::Key::Delete);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Add, CEGUI::Key::Add);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Subtract, CEGUI::Key::Subtract);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Multiply, CEGUI::Key::Multiply);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Divide, CEGUI::Key::Divide);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Left, CEGUI::Key::ArrowLeft);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Right, CEGUI::Key::ArrowRight);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Up, CEGUI::Key::ArrowUp);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Down, CEGUI::Key::ArrowDown);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Numpad0, CEGUI::Key::Numpad0);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Numpad1, CEGUI::Key::Numpad1);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Numpad2, CEGUI::Key::Numpad2);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Numpad3, CEGUI::Key::Numpad3);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Numpad4, CEGUI::Key::Numpad4);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Numpad5, CEGUI::Key::Numpad5);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Numpad6, CEGUI::Key::Numpad6);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Numpad7, CEGUI::Key::Numpad7);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Numpad8, CEGUI::Key::Numpad8);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Numpad9, CEGUI::Key::Numpad9);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::F1, CEGUI::Key::F1);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::F2, CEGUI::Key::F2);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::F3, CEGUI::Key::F3);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::F4, CEGUI::Key::F4);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::F5, CEGUI::Key::F5);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::F6, CEGUI::Key::F6);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::F7, CEGUI::Key::F7);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::F8, CEGUI::Key::F8);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::F9, CEGUI::Key::F9);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::F10, CEGUI::Key::F10);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::F11, CEGUI::Key::F11);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::F12, CEGUI::Key::F12);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::F13, CEGUI::Key::F13);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::F14, CEGUI::Key::F14);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::F15, CEGUI::Key::F15);
			m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Pause, CEGUI::Key::Pause);
		}

		const CEGUI::Key::Scan& translateKey(const sf::Keyboard::Key& key)
		{
			const auto it = m_mapSFKeyToCEGUIKey.find(key);
			return it->second; // we get key events from SFML, so the "UNKNOWN" key should never get called here
		}

		const CEGUI::MouseButton& translateMouse(const sf::Mouse::Button& button)
		{
			const auto it = m_mapSFMouseButtonToCEGUIMouseButton.find(button);
			return it->second; // we get key events from SFML, so the "UNKNOWN" key should never get called here
		}

	private:
		std::unordered_map<sf::Keyboard::Key, CEGUI::Key::Scan>   m_mapSFKeyToCEGUIKey;
		std::unordered_map<sf::Mouse::Button, CEGUI::MouseButton> m_mapSFMouseButtonToCEGUIMouseButton;
	};

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

		// Responsible for translating the SFML input IDs to CEGUI used ones for injection.
		SFMLtoCEGUIInputTranslator m_InputTranslator;
	};
}