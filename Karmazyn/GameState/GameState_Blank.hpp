#pragma once

#include "IGameState.hpp"

namespace Karmazyn
{
	class GameState_Blank : public IGameState
	{
	public:
		GameState_Blank(GameEngine& engine) : IGameState(engine) {}
		~GameState_Blank() override { }

		void update(uint64_t diff) override { }
		void render() override { }
		void handleEvent(const sf::Event& event) override { }
	};
}