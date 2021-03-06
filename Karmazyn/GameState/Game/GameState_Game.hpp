#pragma once
#include "../IGameState.hpp"

namespace Karmazyn
{
	class Engine; class UIManager; 


	class GameState_Game : public IGameState
	{
		struct GameInitParams
		{
			GameInitParams(int i)
			{

			}
		};

	public:
		GameState_Game(Engine& engine, const GameInitParams& params);
		~GameState_Game() override;

#pragma region IGameState_Implementation
		void update(float diff) override;
		void render() const override;
		void handleEvent(const sf::Event& event) override;
#pragma endregion

	private:
		
	};
}