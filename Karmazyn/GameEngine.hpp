#pragma once
#include <SFML/Graphics.hpp>
#include <Config.hpp>

#include <atomic>
#include <stack>
#include <memory>
#include <thread>

#include "GameState/IGameState.hpp"

namespace Karmazyn
{
	class IGameState;

	class GameEngine
	{
		// Helper class, providing a safer top() behaviour, that is guaranteed to return a valid reference.
		class GameStateStack
		{
		public:
			void emplace(std::unique_ptr<IGameState>&& what) { m_UnderlyingStack.emplace(std::move(what)); }
			void pop() { m_UnderlyingStack.pop(); }
			//void push(std::unique_ptr<IGameState>&& what) { m_UnderlyingStack.push(what); }

			std::unique_ptr<IGameState>& top()
			{
				if (m_UnderlyingStack.size() == 0)
					return m_Default;

				return m_UnderlyingStack.top();
			}

		private:
			std::unique_ptr<IGameState> m_Default;
			std::stack<std::unique_ptr<IGameState>> m_UnderlyingStack;
		};

	public:
		GameEngine();

		int Run();

		// Stops the render thread (and joins+destroys), and closes the render window.
		void Stop();

		sf::RenderWindow& getRenderWindow() { return m_RenderWindow; }
	private:
		GameEngine(const GameEngine&) = delete;
		GameEngine(GameEngine&&) = delete;
		const GameEngine& operator=(const GameEngine&) = delete;
		const GameEngine& operator=(GameEngine&&) = delete;

		Config m_Config;
		sf::RenderWindow m_RenderWindow;

		// This thread:
		// 1. clears renderwindow
		// 2. calls m_GameStates.top().render();
		// 3. draws renderwindow
		std::unique_ptr<std::thread> m_RenderThread;
		std::atomic<bool> m_RunRenderThread;

		// The currently present game states. 
		// The top of the stack will receive the calls from the main game loop (event, update, render), only.
		GameStateStack m_GameStates;
	};
}