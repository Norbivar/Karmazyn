#include "GameState_Game.hpp"
#include "../../Engine.hpp"
#include "../../UIManager/UIManager.hpp"

namespace Karmazyn
{
	GameState_Game::GameState_Game(Engine& engine, const GameInitParams& params) :
		IGameState(engine),
		theUI(engine.getUIManager())
	{
		CEGUI::Window* root = theUI.getSystem().getDefaultGUIContext().getRootWindow();
	}

	GameState_Game::~GameState_Game()
	{

	}

#pragma region IGameState_Implementation

	void GameState_Game::handleEvent(const sf::Event& event)
	{
		if (theUI.handleEvent(event))
			return;
	}
	void GameState_Game::render() const
	{
		theUI.draw();
	}
	void GameState_Game::update(float diff)
	{

	}
#pragma endregion
}