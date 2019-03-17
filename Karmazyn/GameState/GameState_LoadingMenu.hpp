#pragma once
#include <CEGUI/CEGUI.h>
#include "../GameEngine.hpp"
#include "IGameState.hpp"

namespace Karmazyn
{
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

		void onLoadingDone(const CEGUI::EventArgs& /*e*/);
		
	private:
		// A shortcut for 'theEngine.getUIManager()'.
		GUIManager& theGUI;

		// Root of the loaded Layout (which is a StaticImage -> the background picture)
		CEGUI::Window* m_LoadingGUIRoot;
		// The elements of the LoadingGUIRoot, saved out for use:
		CEGUI::NamedElement*      m_VersionLabel;
		CEGUI::NamedElement*      m_TippLabel;
		CEGUI::NamedElement*      m_LoadingLabel;
		CEGUI::ProgressBar*       m_LoadingProgressbar;
	};
}