#pragma once
#include "../IGameState.hpp"
#include <vector>
#include <CEGUI/CEGUI.h>

namespace Karmazyn
{
	class Engine; class UIManager;

	struct GameInitParams
	{
		std::string
	};

	class GameState_Game : public IGameState
	{
	public:
		GameState_Game(Engine& engine, const GameInitParams& params);
		~GameState_Game() override;

#pragma region IGameState_Implementation
		void update(float diff) override;
		void render() const override;
		void handleEvent(const sf::Event& event) override;
#pragma endregion

	private:
		// A shortcut for 'theEngine.getUIManager()'.
		UIManager& theUI;


		using IngameMap = std::vector<std::vector<int>>;
		IngameMap m_Map;
	};
}