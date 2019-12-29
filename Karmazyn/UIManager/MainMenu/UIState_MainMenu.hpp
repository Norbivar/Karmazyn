#pragma  once

#include "../IUIState.hpp"

namespace Karmazyn
{
	class GameState_MainMenu;

	class UIState_MainMenu : public IUIState
	{
	public:
		explicit UIState_MainMenu(UIManager& uimanager, GameState_MainMenu& gamestate);
		virtual ~UIState_MainMenu() override { }

	private:
		GameState_MainMenu& theGameState;

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
				CEGUI::ToggleButton*    m_OptionVSyncCheckbox; // nested in VsyncLabel
				CEGUI::ToggleButton*    m_OptionWindowedModeCheckbox; // nested in WindowedModeLabel
				CEGUI::Editbox*         m_OptionResolutionWidth;
				CEGUI::Editbox*         m_OptionResolutionHeight;
				CEGUI::Window*          m_RestartNotificationLabel;
			//TODO: finish options window

		void onNewGameClicked (const CEGUI::EventArgs& /*e*/);
		void onLoadGameClicked(const CEGUI::EventArgs& /*e*/);
		void onOptionsClicked (const CEGUI::EventArgs& /*e*/);
		void onQuitGameClicked(const CEGUI::EventArgs& /*e*/);

	public:
		void show();
		void hide();
	};
}