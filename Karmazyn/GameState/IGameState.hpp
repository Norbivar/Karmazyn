#pragma once

#include <cstdint>
#include <SFML/Window/Event.hpp>

namespace Karmazyn
{
	class Engine;
	class IGameState
	{
	public:
		IGameState(Engine& engine);
		virtual ~IGameState() { }

		// Called periodically.
		virtual void update(float diff) = 0;

		// You should queue up (draw(...)) all your drawables in this function. Clearing and displaying is handled by the render thread.
		virtual void render() const = 0;

		// Called whenever there is an event to process.
		virtual void handleEvent(const sf::Event& event) = 0;

		// Called before the GameState would become active through either transition or backtrace (popping the game state stack).
		// Widely used for showing GameState specific GUI elements.
		virtual void afterTransitionedIn() {};

		// Called before we transition from this state to another.
		// Widely used for hiding/disabling GameState specific GUI elements.
		virtual void beforeTransitionedOut() {};
	protected:
		Engine& theEngine;
	};
}