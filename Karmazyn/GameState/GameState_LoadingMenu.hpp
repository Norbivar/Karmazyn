#pragma once
#include "../GameEngine.hpp"
#include "IGameState.hpp"

namespace Karmazyn
{
	class GameState_LoadingMenu : public IGameState
	{
	public:
		GameState_LoadingMenu(GameEngine& engine);
		~GameState_LoadingMenu() override;

		#pragma region IGameState_Implementation
		void update(uint64_t diff) override;
		void render() override;
		void handleEvent(const sf::Event& event) override;
		#pragma endregion
		
	private:
	};
}