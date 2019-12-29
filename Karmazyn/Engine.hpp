#pragma once
#include <RenderWindow/RenderWindow.hpp>

namespace Karmazyn
{
	class AssetManager; class UIManager; class GameStateMachine;

	class Engine
	{
	public:
		Engine();
		~Engine(); // otherwise the default destructor will cry not knowing how to delete pointers of uncomplete types


		// Initializes the RenderWindow with references to the UI manager and GameStateMachine.
		// Also starts the main event loop, that handles ticks and SFML events, which get pushed to the current active state.
		int Run();
		// Stops the render thread, attaches it to the current thread and then stops the main event loop, resulting in a shutdown.
		void Stop();

		RenderWindow&     getRenderWindow()     { return m_RenderWindow; }
		AssetManager&     getAssetManager()     { return *m_Assets; }
		UIManager&        getUIManager()        { return *m_UI; }
		GameStateMachine& getGameStateMachine() { return *m_GameStateMachine; }

		// These functions pretty much delegate calls to the RenderWindow (Graphics) and CEGUI if necessary.
		void changeScreenSize(const unsigned int newWidth, const unsigned int newHeight);
		void changeVerticalSynced(bool enabled);
		void changeWindowedMode(bool enabled);

	private:
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;
		const Engine& operator=(const Engine&) = delete;
		const Engine& operator=(Engine&&) = delete;

		std::unique_ptr<AssetManager> m_Assets;
		std::unique_ptr<UIManager>    m_UI;

		std::atomic<bool> m_CoreLoopRunning;

		// The currently present game states. 
		// The top of the stack will receive the calls from the main game loop (event, update, render), only.
		std::unique_ptr<GameStateMachine> m_GameStateMachine;

		RenderWindow                  m_RenderWindow;
	};
}