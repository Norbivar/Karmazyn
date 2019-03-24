#pragma once
#include <stack>
#include <memory>


namespace Karmazyn
{
	// Helper class, providing a safer top() behaviour, that is guaranteed to return a valid reference.
	class IGameState; class GameEngine;

	class GameStateStack
	{
	public:
		GameStateStack(GameEngine& engine);

		void push(std::unique_ptr<IGameState>&& what);
		void swapTop(std::unique_ptr<IGameState>& what);
		void pop();

		std::unique_ptr<IGameState>& top();

	private:
		std::stack<std::unique_ptr<IGameState>> m_UnderlyingStack;
		
		GameEngine& theEngine;
		friend class GameEngine;
	};
}