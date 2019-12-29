#pragma once

namespace Karmazyn
{
	// Translates keyboard and mouse events from their SFML ID to CEGUI used ID.
	class SFMLtoCEGUIInputTranslator
	{
	public:
		constexpr SFMLtoCEGUIInputTranslator() :
			m_SFKeyToCEGUIKey{
			{
				CEGUI::Key::A,
				CEGUI::Key::B,
				CEGUI::Key::C,
				CEGUI::Key::D,
				CEGUI::Key::E,
				CEGUI::Key::F,
				CEGUI::Key::G,
				CEGUI::Key::H,
				CEGUI::Key::I,
				CEGUI::Key::J,
				CEGUI::Key::K,
				CEGUI::Key::L,
				CEGUI::Key::M,
				CEGUI::Key::N,
				CEGUI::Key::O,
				CEGUI::Key::P,
				CEGUI::Key::Q,
				CEGUI::Key::R,
				CEGUI::Key::S,
				CEGUI::Key::T,
				CEGUI::Key::U,
				CEGUI::Key::V,
				CEGUI::Key::W,
				CEGUI::Key::X,
				CEGUI::Key::Y,
				CEGUI::Key::Z,
				CEGUI::Key::Zero,
				CEGUI::Key::One,
				CEGUI::Key::Two,
				CEGUI::Key::Three,
				CEGUI::Key::Four,
				CEGUI::Key::Five,
				CEGUI::Key::Six,
				CEGUI::Key::Seven,
				CEGUI::Key::Eight,
				CEGUI::Key::Nine,
				CEGUI::Key::Escape,
				CEGUI::Key::LeftControl,
				CEGUI::Key::LeftShift,
				CEGUI::Key::LeftAlt,
				CEGUI::Key::LeftWindows,
				CEGUI::Key::RightControl,
				CEGUI::Key::RightShift,
				CEGUI::Key::RightAlt,
				CEGUI::Key::RightWindows,
				CEGUI::Key::LeftBracket,
				CEGUI::Key::RightBracket,
				CEGUI::Key::Semicolon,
				CEGUI::Key::Comma,
				CEGUI::Key::Period,
				CEGUI::Key::Apostrophe,
				CEGUI::Key::Slash,
				CEGUI::Key::Backslash,
				CEGUI::Key::Grave,
				CEGUI::Key::Equals,
				CEGUI::Key::Minus,
				CEGUI::Key::Space,
				CEGUI::Key::Return,
				CEGUI::Key::Backspace,
				CEGUI::Key::Tab,
				CEGUI::Key::PageUp,
				CEGUI::Key::PageDown,
				CEGUI::Key::End,
				CEGUI::Key::Home,
				CEGUI::Key::Insert,
				CEGUI::Key::Delete,
				CEGUI::Key::Add,
				CEGUI::Key::Subtract,
				CEGUI::Key::Multiply,
				CEGUI::Key::Divide,
				CEGUI::Key::ArrowLeft,
				CEGUI::Key::ArrowRight,
				CEGUI::Key::ArrowUp,
				CEGUI::Key::ArrowDown,
				CEGUI::Key::Numpad0,
				CEGUI::Key::Numpad1,
				CEGUI::Key::Numpad2,
				CEGUI::Key::Numpad3,
				CEGUI::Key::Numpad4,
				CEGUI::Key::Numpad5,
				CEGUI::Key::Numpad6,
				CEGUI::Key::Numpad7,
				CEGUI::Key::Numpad8,
				CEGUI::Key::Numpad9,
				CEGUI::Key::F1,
				CEGUI::Key::F2,
				CEGUI::Key::F3,
				CEGUI::Key::F4,
				CEGUI::Key::F5,
				CEGUI::Key::F6,
				CEGUI::Key::F7,
				CEGUI::Key::F8,
				CEGUI::Key::F9,
				CEGUI::Key::F10,
				CEGUI::Key::F11,
				CEGUI::Key::F12,
				CEGUI::Key::F13,
				CEGUI::Key::F14,
				CEGUI::Key::F15,
				CEGUI::Key::Pause
			}},
			m_SFMouseButtonToCEGUIMouseButton{ 
			{
				CEGUI::MouseButton::LeftButton,
				CEGUI::MouseButton::RightButton,
				CEGUI::MouseButton::MiddleButton,
				CEGUI::MouseButton::X1Button,
				CEGUI::MouseButton::X2Button
			}}
		{
			// EVERY KEY IS CONTAINED IN AN ARRAY, PLEASE   !!! ENSURE !!!   THAT KEYS EMPLACED IN THE CONTAINERS ARE THE GOOD ORDER (and fill potential gaps where they exist in SFML)

			// Keys from SFML to CEGUI:
			// m_mapSFKeyToCEGUIKey.emplace(sf::Keyboard::Unknown, CEGUI::Key::Unknown);// TODO: handle this with the vector-approach
		}

		// Returns the corresponding CEGUI key for the given SFML key.
		constexpr const CEGUI::Key::Scan& translateKey(const sf::Keyboard::Key& key) const
		{
			return m_SFKeyToCEGUIKey[key];
		}

		// Returns the corresponding CEGUI mouse button for the givem SFML mouse button.
		constexpr const CEGUI::MouseButton& translateMouse(const sf::Mouse::Button& button) const
		{
			return m_SFMouseButtonToCEGUIMouseButton[button];
		}
		
	private:
		// Holds the CEGUI keys in a continious storage. Due to the nature of SFML key declarations, CEGUI keys can be retrieved by indexing the vector with the SFML key ID.
		// Vectors for the above two are possible because the SFML nicely defines keys in an enum, continiously (implicitly), so there will be no gap if the order of their appearance is preserved.
		std::array<CEGUI::Key::Scan,   sf::Keyboard::KeyCount> m_SFKeyToCEGUIKey;  // much better than unordered_map, as it is continious and cacheable as sh*t
		std::array<CEGUI::MouseButton, sf::Mouse::ButtonCount> m_SFMouseButtonToCEGUIMouseButton;
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