#pragma once
#include "IGameState.hpp"
#include <CEGUI/CEGUI.h>

namespace Karmazyn
{

	class GameEngine; class UIManager;

	class GameState_MainMenu : public IGameState
	{
	public:
		GameState_MainMenu(GameEngine& engine);
		~GameState_MainMenu() override;

#pragma region IGameState_Implementation
		void update(float diff) override;
		void render() const override;
		void handleEvent(const sf::Event& event) override;
#pragma endregion

	private:
		// A shortcut for 'theEngine.getUIManager()'.
		UIManager& theUI;

		// Root of the loaded Layout (which is a StaticImage -> the background picture)
		// The tabulation of rows show parent-child relationships
		CEGUI::Window* m_MainMenuRoot;
			CEGUI::NamedElement*      m_MainMenuWindow;
				CEGUI::PushButton*      m_NewGameButton;
				CEGUI::PushButton*      m_LoadGameButton;
				CEGUI::PushButton*      m_OptionsButton;
				CEGUI::PushButton*      m_QuitGameButton;
				CEGUI::NamedElement*    m_VersionLabel;
			CEGUI::Window*      m_OptionsWindow;
			//TODO: finish options window

		void onNewGameClicked (const CEGUI::EventArgs& /*e*/);
		void onLoadGameClicked(const CEGUI::EventArgs& /*e*/);
		void onOptionsClicked (const CEGUI::EventArgs& /*e*/);
		void onQuitGameClicked(const CEGUI::EventArgs& /*e*/);
	};
}