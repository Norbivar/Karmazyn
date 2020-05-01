#include "GameState_Game.hpp"
#include "../../Engine.hpp"
#include "../../UIManager/UIManager.hpp"

namespace Karmazyn
{
	GameState_Game::GameState_Game(Engine& engine, const GameInitParams& params) :
		IGameState(engine)
	{

	}

	GameState_Game::~GameState_Game()
	{

	}

#pragma region IGameState_Implementation

	void GameState_Game::handleEvent(const sf::Event& event)
	{
	}
	void GameState_Game::render() const
	{

	}
	void GameState_Game::update(float diff)
	{

	}
#pragma endregion
}