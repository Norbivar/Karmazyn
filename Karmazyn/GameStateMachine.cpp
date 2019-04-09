#include "GameStateMachine.hpp"
#include <Logger.hpp>

#include "CEGUI/CEGUI.h"
#include "GameEngine.hpp"
#include "UIManager/UIManager.hpp"
#include "GameState/GameState_Blank.hpp"

namespace Karmazyn
{
	GameStateMachine::GameStateMachine(GameEngine & engine) :
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
	}

	void GameStateMachine::clearHistory()
	{
		while (!m_HitStates.empty())
			m_HitStates.pop();
	}
}