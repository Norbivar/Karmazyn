#include "GameStateStack.hpp"

#include "GameState/GameState_Blank.hpp"

namespace Karmazyn
{
	GameStateStack::GameStateStack(GameEngine& engine) :
		m_Default{ std::make_unique<GameState_Blank>(engine)}
	{

	}
	void GameStateStack::emplace(std::unique_ptr<IGameState>&& what)
	{
		m_UnderlyingStack.emplace(std::forward<std::unique_ptr<IGameState>>(what));
	}
	void GameStateStack::pop()
	{
		m_UnderlyingStack.pop();
	}
	std::unique_ptr<IGameState>& GameStateStack::top()
	{
		if (m_UnderlyingStack.size() == 0)
			return m_Default;

		return m_UnderlyingStack.top();
	}
}