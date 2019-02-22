#pragma once

#include <cstdint>

namespace Karmazyn
{
	class Application;

	class IGameState
	{
	public:
		IGameState(Application* app) : m_Application(app) { }
		virtual ~IGameState() { }

		virtual void update(uint32_t diff) = 0;
		virtual void render() = 0;
		virtual void handleInput() = 0;

	protected:
		Application* m_Application;
	};
}