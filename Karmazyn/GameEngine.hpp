#pragma once
#include <RenderWindow/RenderWindow.hpp>
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
		void Stop();

		RenderWindow&     getRenderWindow()   { return m_RenderWindow; }
		AssetManager&     getAssetManager()   { return *m_Assets; }
		UIManager&        getUIManager()      { return *m_UI; }
		GameStateStack&   getGameStateStack() { return *m_GameStates; }

		void changeScreenSize(const unsigned int newWidth, const unsigned int newHeight);
		void changeVerticalSynced(bool enabled);

	private:
		GameEngine(const GameEngine&) = delete;
		GameEngine(GameEngine&&) = delete;
		const GameEngine& operator=(const GameEngine&) = delete;
		const GameEngine& operator=(GameEngine&&) = delete;

		std::unique_ptr<AssetManager> m_Assets;
		std::unique_ptr<UIManager>    m_UI;

		std::atomic<bool> m_CoreLoopRunning;

		// The currently present game states. 
		// The top of the stack will receive the calls from the main game loop (event, update, render), only.
		std::unique_ptr<GameStateStack> m_GameStates;

		RenderWindow                  m_RenderWindow;
	};
}