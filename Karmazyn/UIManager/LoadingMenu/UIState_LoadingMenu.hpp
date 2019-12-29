#pragma once

#include "../IUIState.hpp"

namespace Karmazyn
{
	class GameState_LoadingMenu; 

	class UIState_LoadingMenu : public IUIState
	{
	public:
		explicit UIState_LoadingMenu(UIManager& uimanager, GameState_LoadingMenu& gamestate);
		virtual ~UIState_LoadingMenu() override { }

	private:
		GameState_LoadingMenu& theGameState;

		// Root of the loaded Layout (which is a StaticImage -> the background picture)
		// The tabulation of rows show parent-child relationships
		CEGUI::Window* m_LoadingGUIRoot;
		  CEGUI::NamedElement* m_TippLabel;
		  CEGUI::ProgressBar* m_LoadingProgressbar;
		    CEGUI::NamedElement* m_LoadingLabel;

		void onLoadingDone(const CEGUI::EventArgs& /*e*/);
		const std::string determineTippText() const;
		const std::string determineLoadingText() const;
	
	public:
		void show();
		void hide();
		void update(float diff);
	};
}