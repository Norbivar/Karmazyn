#pragma once

#include "IGameState.hpp"

class GameState_Blank : public IGameState
{
	~GameState_Blank() override { }

	void update(uint64_t diff) override { }
	void render() override { }
	void handleEvent(const sf::Event& event) override { }
};