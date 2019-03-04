#include <Logger.hpp>

#include "GameState_LoadingMenu.hpp"

namespace Karmazyn
{
	GameState_LoadingMenu::GameState_LoadingMenu(GameEngine& engine) :
		IGameState(engine),
		shape(20.f)
	{
		shape.setOrigin({ 20.0f, 20.0f });
		shape.setFillColor(sf::Color(100, 250, 50));
	}
	GameState_LoadingMenu::~GameState_LoadingMenu()
	{

	}

	void GameState_LoadingMenu::handleEvent(const sf::Event& event)
	{
		switch (event.type)
		{
			case sf::Event::MouseMoved:
			{
				sf::Vector2f pos = { static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };
				shape.setPosition(pos);
				break;
			}
			case sf::Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == sf::Mouse::Button::Left)
				{
					sf::CircleShape tmp(5.0f);
					tmp.setPosition(
						static_cast<float>(event.mouseButton.x), 
						static_cast<float>(event.mouseButton.y)
					);
					shapesToFuckAroundWith.emplace_back(std::move(tmp));
				}
				else if (event.mouseButton.button == sf::Mouse::Button::Right)
				{
					m_Engine.Stop();
				}
				break;
			}
		}
	}
	void GameState_LoadingMenu::render() // called by a different thread, but .draw() takes const ref, so it should be fine
	{
		for (const auto& it : shapesToFuckAroundWith)
			m_Engine.getRenderWindow().draw(it);

		m_Engine.getRenderWindow().draw(shape);
	}
	void GameState_LoadingMenu::update(uint64_t diff)
	{

	}
}