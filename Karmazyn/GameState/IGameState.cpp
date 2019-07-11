#include "Engine.hpp"
#include "IGameState.hpp"

Karmazyn::IGameState::IGameState(Engine& engine) :
	theEngine(engine)
{ }
