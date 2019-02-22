#pragma once

#include "IGameState.hpp"

namespace Karmazyn
{
	class GameState_Menu : public IGameState
	{
	public:
		GameState_Menu(Application* app);
		~GameState_Menu() override;

		void update(uint32_t diff) override;
		void render() override;
		void handleInput() override;
	};
}