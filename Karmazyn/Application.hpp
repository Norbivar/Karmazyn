#pragma once
#include <SFML/Graphics.hpp>

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

		sf::RenderWindow m_RenderWindow;
	};
}