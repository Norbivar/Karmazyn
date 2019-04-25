#pragma once

#include "IGameState.hpp"

namespace Karmazyn
{
	class GameState_Blank : public IGameState
	{
	public:
		GameState_Blank(Engine& engine) : IGameState(engine) {}
		~GameState_Blank() override { }

		void update(float diff) override { }
		void render() const override { }
		void handleEvent(const sf::Event& event) override { }
	};
}