#pragma once

#include <cstdint>
#include <SFML/Window/Event.hpp>

namespace Karmazyn
{
	class GameEngine;
	class IGameState
	{
	public:
		IGameState(GameEngine& engine);
		virtual ~IGameState() { }

		// Called periodically.
		virtual void update(uint64_t diff) = 0;

		// You should queue up (draw(...)) all your drawables in this function. Clearing and displaying is handled by the render thread.
		virtual void render() = 0;

		// Called whenever there is an event to process.
		virtual void handleEvent(const sf::Event& event) = 0;

	protected:
		GameEngine& m_Engine;
	};
}