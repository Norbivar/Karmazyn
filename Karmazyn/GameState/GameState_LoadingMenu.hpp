#pragma once
#include <SFML/Graphics.hpp>
#include "../GameEngine.hpp"
#include "IGameState.hpp"

namespace Karmazyn
{
	class GameState_LoadingMenu : public IGameState
	{
	public:
		GameState_LoadingMenu(GameEngine& engine);
		~GameState_LoadingMenu() override;

		bool update(float diff) override;
		bool render() override;
		bool handleEvent(const sf::Event& event) override;
	private:
		sf::CircleShape shape;
	};
}