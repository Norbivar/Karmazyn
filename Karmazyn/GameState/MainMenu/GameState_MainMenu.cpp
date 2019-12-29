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

	void GameState_MainMenu::onChangeScreenSize(unsigned int width, unsigned int height) 
	{
		theEngine.changeScreenSize(width, height); 
	}
	void GameState_MainMenu::onVerticalSyncChanged(bool newValue) 
	{ 
		theEngine.changeVerticalSynced(newValue); 
	}
	void GameState_MainMenu::onWindowedModeChanged(bool newValue) 
	{ 
		theEngine.changeWindowedMode(newValue);
	}

	void GameState_MainMenu::onQuitGameClicked()
	{
		theEngine.Stop();
	}
}