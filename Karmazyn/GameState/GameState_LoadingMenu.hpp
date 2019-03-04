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

		void update(uint64_t diff) override;
		void render() override;
		void handleEvent(const sf::Event& event) override;
	private:
		sf::CircleShape shape;
		std::vector<sf::CircleShape> shapesToFuckAroundWith;
	};
}