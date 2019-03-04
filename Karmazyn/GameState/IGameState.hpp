#pragma once

#include <cstdint>
#include <SFML/Window/Event.hpp>

namespace Karmazyn
{
	class GameEngine;

	class IGameState
	{
	public:
		IGameState(GameEngine& engine) : m_Engine(engine) { }
		virtual ~IGameState() { }

		// Each of the below methods return value is a signal to the core: 
		//	if a function returns true, it will swallow that triggering of event: it will not be sent to subsequent layers

		virtual void update(uint64_t diff) = 0;
		virtual void render() = 0;
		virtual void handleEvent(const sf::Event& event) = 0;

	protected:
		GameEngine& m_Engine;
	};
}