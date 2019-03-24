#pragma once
#include <CEGUI/CEGUI.h>
#include "IGameState.hpp"

namespace Karmazyn
{
	class GameEngine; class UIManager;
	class GameState_LoadingMenu : public IGameState
	{
	public:
		GameState_LoadingMenu(GameEngine& engine);
		~GameState_LoadingMenu() override;

		#pragma region IGameState_Implementation
		void update(float diff) override;
		void render() const override;
		void handleEvent(const sf::Event& event) override;
		#pragma endregion

		std::string determineTippText();
		std::string determineLoadingText();	
	private:
		// A shortcut for 'theEngine.getUIManager()'.
		UIManager& theUI;

		// Root of the loaded Layout (which is a StaticImage -> the background picture)
		// The tabulation of rows show parent-child relationships
		CEGUI::Window* m_LoadingGUIRoot;
			CEGUI::NamedElement*      m_VersionLabel;
			CEGUI::NamedElement*      m_TippLabel;
			CEGUI::ProgressBar*       m_LoadingProgressbar;
				CEGUI::NamedElement*      m_LoadingLabel;

		void onLoadingDone(const CEGUI::EventArgs& /*e*/);
	};
}