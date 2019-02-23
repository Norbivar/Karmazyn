#include "GameStateMenu.hpp"
#include <Logger.hpp>

namespace Karmazyn
{
	GameState_Menu::GameState_Menu(Application* app) :
		IGameState(app)
	{

	}
	GameState_Menu::~GameState_Menu()
	{

	}

	void GameState_Menu::handleInput()
	{
		theLog->info("HANDLE INPUT");
	}
	void GameState_Menu::render()
	{

	}
	void GameState_Menu::update(uint32_t diff)
	{

	}
}