#pragma once
#include <SFML/Graphics.hpp>
#include <Config.hpp>

#include <stack>
#include <memory>

#include "GameState/IGameState.hpp"

namespace Karmazyn
{
	class Application
	{
	public:
		Application();

		int Run();

	private:
		Application(const Application&) = delete;
		Application(Application&&) = delete;
		const Application& operator=(const Application&) = delete;
		const Application& operator=(Application&&) = delete;

		Config m_Config;
		sf::RenderWindow m_RenderWindow;
		std::stack<std::unique_ptr<IGameState>> m_GameStateStack;
	};
}