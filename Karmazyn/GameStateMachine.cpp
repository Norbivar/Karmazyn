#include "GameStateMachine.hpp"
#include <Logger.hpp>

#include "CEGUI/CEGUI.h"
#include "Engine.hpp"
#include "UIManager/UIManager.hpp"
#include "GameState/GameState_Blank.hpp"

namespace Karmazyn
{
	GameStateMachine::GameStateMachine(Engine& engine) :
		theEngine{ engine }
	{
		transition<GameState_Blank>();
	}
	GameStateMachine::~GameStateMachine()
	{

	}
	void GameStateMachine::transitionBack()
	{
		if (!m_HitStates.empty())
		{
			m_CurrentState.swap(m_HitStates.top());
			m_HitStates.pop();
		}
		else throw InvalidStateMachineTransitionException("transitionBack() requested with empty stack!");
	}

	void GameStateMachine::clearHistory()
	{
		while (!m_HitStates.empty())
			m_HitStates.pop();
	}
}