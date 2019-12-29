#include "GameState_LoadingMenu.hpp"
#include "../../Engine.hpp"
#include "../../GameStateMachine.hpp"

#include "../../UIManager/LoadingMenu/UIState_LoadingMenu.hpp"

namespace Karmazyn
{
	GameState_LoadingMenu::GameState_LoadingMenu(Engine& engine) :
		IGameState{engine}
	{
		theUIState = std::make_unique<UIState_LoadingMenu>(engine.getUIManager(), *this);
	}
	GameState_LoadingMenu::~GameState_LoadingMenu()
	{
	
	}

#pragma region IGameState_Implementation

	void GameState_LoadingMenu::handleEvent(const sf::Event& event)
	{

	}
	void GameState_LoadingMenu::afterTransitionedIn()
	{
		theUIState->show();
	}
	void GameState_LoadingMenu::beforeTransitionedOut()
	{
		theUIState->hide();
	}
	void GameState_LoadingMenu::render() const // called by a different thread, but .draw() takes const ref, so it should be fine
	{

	}
	void GameState_LoadingMenu::update(float diff)
	{
		theUIState->update(diff);
	}
#pragma endregion
}