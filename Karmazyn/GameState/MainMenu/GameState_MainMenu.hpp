#pragma once
#include "../IGameState.hpp"

namespace Karmazyn
{
	class UIState_MainMenu;

	class GameState_MainMenu :
		public IGameState
	{
	public:
		GameState_MainMenu(Engine& engine);
		~GameState_MainMenu() override;

#pragma region IGameState_Implementation
		void update(float diff) override;
		void render() const override;
		void handleEvent(const sf::Event& event) override;

		void afterTransitionedIn() override;
		void beforeTransitionedOut() override;
#pragma endregion

		void onChangeScreenSize(unsigned int width, unsigned int height);
		void onVerticalSyncChanged(bool newValue);
		void onWindowedModeChanged(bool newValue);

		void onQuitGameClicked();
	private:
		std::unique_ptr<UIState_MainMenu> theUIState;
	};
}