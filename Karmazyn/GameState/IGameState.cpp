#include "GameEngine.hpp"
#include "IGameState.hpp"

Karmazyn::IGameState::IGameState(GameEngine & engine) :
	m_Engine(engine)
{ }
