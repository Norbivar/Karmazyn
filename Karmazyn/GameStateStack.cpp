#include "GameStateStack.hpp"
#include <Logger.hpp>

#include "CEGUI/CEGUI.h"
#include "GameEngine.hpp"
#include "UIManager/UIManager.hpp"
#include "GameState/GameState_Blank.hpp"

namespace Karmazyn
{
	GameStateStack::GameStateStack(GameEngine& engine) :
		theEngine(engine)
	{

		m_UnderlyingStack.emplace(std::make_unique<GameState_Blank>(engine));
	}
	void GameStateStack::push(std::unique_ptr<IGameState>&& what)
	{
		m_UnderlyingStack.emplace(std::move(what));
	}

	void GameStateStack::swapTop(std::unique_ptr<IGameState>& what)
	{
		if (m_UnderlyingStack.size() == 2)
		{
			what.swap(top());
		}
		else
			theLog->error("GameStateStack: Tried replacing empty stacks top!");
	}

	void GameStateStack::pop()
	{
		if (m_UnderlyingStack.size() == 1) // a fallback must always be guaranteed to be in the stack
			return;

		m_UnderlyingStack.pop();
	}
	std::unique_ptr<IGameState>& GameStateStack::top()
	{
		return m_UnderlyingStack.top();
	}
}