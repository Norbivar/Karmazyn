#include "GameState_MainMenu.hpp"

#include "../../Engine.hpp"
#include "../../UIManager/MainMenu/UIState_MainMenu.hpp"
#include "../../GameStateMachine.hpp"

#include "../Game/GameState_Game.hpp"

namespace Karmazyn
{
	GameState_MainMenu::GameState_MainMenu(Engine& engine) :
		IGameState(engine)
	{
		theUIState = std::make_unique<UIState_MainMenu>(engine.getUIManager(), *this);
	}

	GameState_MainMenu::~GameState_MainMenu()
	{
		
	}

#pragma region IGameState_Implementation
	void GameState_MainMenu::update(float diff)
	{

	}

	void GameState_MainMenu::render() const
	{

	}

	void GameState_MainMenu::handleEvent(const sf::Event& event)
	{

	}
	void GameState_MainMenu::afterTransitionedIn()
	{
		theUIState->show();
	}
	void GameState_MainMenu::beforeTransitionedOut()
	{
		theUIState->hide();
	}
#pragma endregion
}