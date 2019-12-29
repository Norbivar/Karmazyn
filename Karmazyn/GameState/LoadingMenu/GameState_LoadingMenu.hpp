#pragma once
#include "../IGameState.hpp"

namespace Karmazyn
{
	class UIState_LoadingMenu;

	class GameState_LoadingMenu : 
		public IGameState
	{
	public:
		GameState_LoadingMenu(Engine& engine);
		~GameState_LoadingMenu() override;

		#pragma region IGameState_Implementation
		void update(float diff) override;
		void render() const override;
		void handleEvent(const sf::Event& event) override;
		void afterTransitionedIn() override;
		void beforeTransitionedOut() override;
		#pragma endregion

		void onLoadingDone();
	private:
		std::unique_ptr<UIState_LoadingMenu> theUIState;
	};
}