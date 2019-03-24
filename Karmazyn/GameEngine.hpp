#pragma once
#include <SFML/Graphics.hpp>
#include <Logger.hpp>
#include <Config.hpp>

#include <atomic>
#include <memory>
#include <thread>

namespace Karmazyn
{
	class AssetManager; class UIManager; class GameStateStack;

	class GameEngine
	{
	public:
		GameEngine();
		~GameEngine(); // otherwise the default destructor will cry not knowing how to delete pointers of uncomplete types

		int Run();

		// Stops the render thread (and joins+destroys), and closes the render window, effectively closing the whole program.
		void Stop();

		sf::RenderWindow& getRenderWindow()   { return m_RenderWindow; }
		AssetManager&     getAssetManager()   { return *m_Assets; }
		UIManager&        getUIManager()      { return *m_UI; }
		GameStateStack&   getGameStateStack() { return *m_GameStates; }

	private:
		GameEngine(const GameEngine&) = delete;
		GameEngine(GameEngine&&) = delete;
		const GameEngine& operator=(const GameEngine&) = delete;
		const GameEngine& operator=(GameEngine&&) = delete;

		bool m_IsRunning;

		Config m_Config;
		sf::RenderWindow m_RenderWindow;
		std::unique_ptr<AssetManager> m_Assets;
		std::unique_ptr<UIManager>    m_UI;

		// This thread:
		// 1. clears renderwindow
		// 2. calls m_GameStates.top().render();
		// 3. draws renderwindow
		std::unique_ptr<std::thread> m_RenderThread;
		std::atomic<bool> m_RunRenderThread;

		// The currently present game states. 
		// The top of the stack will receive the calls from the main game loop (event, update, render), only.
		std::unique_ptr<GameStateStack> m_GameStates;
	};
}