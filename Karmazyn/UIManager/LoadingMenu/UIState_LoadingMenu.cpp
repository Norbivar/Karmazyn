
#include "UIState_LoadingMenu.hpp"
#include "../UIManager.hpp"
#include "../../GameState/LoadingMenu/GameState_LoadingMenu.hpp"
#include "../../GameState/MainMenu/GameState_MainMenu.hpp"

#include <Engine.hpp> // TODO: remove these two
#include <GameStateMachine.hpp>


namespace Karmazyn
{
	UIState_LoadingMenu::UIState_LoadingMenu(UIManager& uimanager, GameState_LoadingMenu& gamestate) :
		IUIState{uimanager},
		theGameState{gamestate}
	{
		CEGUI::Window* root = theUI.getSystem().getDefaultGUIContext().getRootWindow();
		m_LoadingGUIRoot = static_cast<CEGUI::Window*>(root->getChildElement("LoadingBackgroundImage"));

		m_LoadingProgressbar = static_cast<CEGUI::ProgressBar*>(m_LoadingGUIRoot->getChildElement("LoadingProgressBar"));
		m_LoadingProgressbar->setProgress(0.0f);
		m_LoadingProgressbar->subscribeEvent(CEGUI::ProgressBar::EventProgressDone, CEGUI::Event::Subscriber(&UIState_LoadingMenu::onLoadingDone, this));
		// Progressbar child:
		{
			m_LoadingLabel = m_LoadingProgressbar->getChildElement("LoadingLabel");
			m_LoadingLabel->setProperty("Text", determineLoadingText());
		}

		m_TippLabel = m_LoadingGUIRoot->getChildElement("TippLabel");
		m_TippLabel->setProperty("Text", determineTippText());
	}

	const std::string UIState_LoadingMenu::determineTippText() const
	{
		return *Utility::Container::getRandomElement(Settings::GUI::LoadingScreenTipps);
	}
	const std::string UIState_LoadingMenu::determineLoadingText() const
	{
		return std::string("Loading Game Assets ...");
	}
	void UIState_LoadingMenu::onLoadingDone(const CEGUI::EventArgs& /*e*/)
	{
		m_LoadingLabel->setProperty("Text", "DONE!");
		theGameState.getEngine().getGameStateMachine().transition<GameState_MainMenu>();
	}


	void UIState_LoadingMenu::show()
	{
		m_LoadingGUIRoot->show();
	}

	void UIState_LoadingMenu::hide()
	{
		m_LoadingGUIRoot->deactivate();
		m_LoadingGUIRoot->hide();
	}
	
	void UIState_LoadingMenu::update(float deltaTime)
	{
		m_LoadingProgressbar->step();
	}
}