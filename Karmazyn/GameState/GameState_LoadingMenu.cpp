#include <Logger.hpp>

#include "GameState_LoadingMenu.hpp"

namespace Karmazyn
{
	GameState_LoadingMenu::GameState_LoadingMenu(GameEngine& engine) :
		IGameState(engine)
	{

	}
	GameState_LoadingMenu::~GameState_LoadingMenu()
	{

	}
#pragma region IGameState_Implementation
	void GameState_LoadingMenu::handleEvent(const sf::Event& event)
	{
//		if (m_GUI.handleEvent(event)) // GUI event will always come first
//			return;
		
		switch (event.type)
		{
			case sf::Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == sf::Mouse::Button::Right)
				{
					m_Engine.Stop();
				}
				break;
			}
		}
	}
	void GameState_LoadingMenu::render() // called by a different thread, but .draw() takes const ref, so it should be fine
	{
//		m_GUI.draw();
	}
	void GameState_LoadingMenu::update(uint64_t diff)
	{

	}
#pragma endregion
}