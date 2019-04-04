#pragma once
#include <atomic>
#include <thread>

#include <Config.hpp>
#include <SFML/Graphics.hpp>

namespace Karmazyn
{
	namespace RenderWindowCommands
	{
		struct Resize
		{
			Resize(unsigned int width, unsigned int height) : newWidth(width), newHeight(height) { }
			unsigned int newWidth, newHeight;
		};
		struct ToggleVSync
		{
			ToggleVSync(bool status) : newStatus(status) { }
			bool newStatus;
		};
	}

	class UIManager; class GameStateStack;
	// Containts references to the UIManager and GameStateStack for the rendering thread. These can safely be stored around, 
	// as by design, the UI and GameStateStack (and Engine related things) should never move around.
	struct RenderThreadReferencePasser {
		RenderThreadReferencePasser(UIManager& ui, GameStateStack& gss) : UI(ui), GameStateStack(gss) {}
		UIManager& UI;
		GameStateStack& GameStateStack;
	};
	// Wrapper for an SFML RenderWindow, aiming to provide the same functionality while encompassing the render logic and potential coupling.
	class RenderWindow
	{	
	public:
		RenderWindow();
		sf::RenderWindow& unwrap() { return m_RenderWindow; }

		// Creates the sf::RenderWindow with m_ContextSettings and m_WindowStyle parameters and given resolution. 
		void create(unsigned int width, unsigned int height);
		// Creates the sf::RenderWindow (by calling create) with config-read resolution.
		void create_from_config();
		// Creates the m_RenderThread, that will 
		void createRenderThreadWith(const RenderThreadReferencePasser& passer);
		void createRenderThread();
		void resetRenderThread();

		template<typename T> void process(T&& command) { static_assert(false, "RenderWindow.process() called with not specialized type!"); }
		template<> void process(RenderWindowCommands::Resize&& command) {
			theConfig->set<int>(Configs::ResolutionX, command.newWidth);
			theConfig->set<int>(Configs::ResolutionY, command.newHeight);
		}
		template<> void process(RenderWindowCommands::ToggleVSync&& command) {
			theConfig->set<int>(Configs::VSync, command.newStatus);
		}

		inline void close()     { resetRenderThread(); m_RenderWindow.close(); }
		inline bool isOpen()    { return m_RenderWindow.isOpen(); }
		inline bool hasFocus()  { return m_RenderWindow.hasFocus(); }
		inline bool pollEvent(sf::Event& ev) { return m_RenderWindow.pollEvent(ev); }
	private:
		std::unique_ptr<RenderThreadReferencePasser> m_ReferencePasser;

		// Underlying SFML RenderWindow.
		sf::RenderWindow m_RenderWindow;

		// This thread calls the SFML drawing primitives: clear, draw, draw ui and display.
		std::unique_ptr<std::thread> m_RenderThread;
		// The render thread checks this atomic variable in every cycle (tied to FPS). Used for stopping+joining the render thread currently.
		std::atomic<bool> m_RunRenderThread;

		// Used to create a RenderWindow that conforms to prebaked settings (OpenGL version, etc)
		sf::ContextSettings m_ContextSettings;
		// Style of the RenderWindow to use (example: frameless, Windows frame, etc)
		int m_WindowStyle;
	};
}