#include "GameState_LoadingMenu.hpp"
#include <Logger.hpp>
#include "../Globals.hpp"
#include "../GameEngine.hpp"
#include "../UIManager/UIManager.hpp"
#include "../GameStateMachine.hpp"
#include "GameState_MainMenu.hpp"


namespace Karmazyn
{
	GameState_LoadingMenu::GameState_LoadingMenu(GameEngine& engine) :
		IGameState(engine),
		theUI(engine.getUIManager())
	{
		CEGUI::Window* root = theUI.getSystem().getDefaultGUIContext().getRootWindow();
		m_LoadingGUIRoot = static_cast<CEGUI::Window*>(root->getChildElement("LoadingBackgroundImage"));

		m_LoadingProgressbar = static_cast<CEGUI::ProgressBar*>(m_LoadingGUIRoot->getChildElement("LoadingProgressBar"));
		m_LoadingProgressbar->setProgress(0.0f);
		m_LoadingProgressbar->subscribeEvent(CEGUI::ProgressBar::EventProgressDone, CEGUI::Event::Subscriber(&GameState_LoadingMenu::onLoadingDone, this));
		// Progressbar child:
		{
			m_LoadingLabel = m_LoadingProgressbar->getChildElement("LoadingLabel");
			m_LoadingLabel->setProperty("Text", determineLoadingText());
		}

		m_TippLabel = m_LoadingGUIRoot->getChildElement("TippLabel");
		m_TippLabel->setProperty("Text", determineTippText());

		m_LoadingGUIRoot->show();
	}
	GameState_LoadingMenu::~GameState_LoadingMenu()
	{
	
	}
	std::string GameState_LoadingMenu::determineTippText()
	{
		std::array<const char*, 2> LoadingScreenTipps = {
			"TODO: these tipps will need to be updated, once there is something to do, as they are pretty much just placeholders, showing the overall picture of the loading screen.",
			"Lorem ipsum doloret sit amet, menjünk dógozni."
		};
		return *Utility::getRandomElement(LoadingScreenTipps);
	}
	std::string GameState_LoadingMenu::determineLoadingText()
	{
		return std::string("Loading Game Assets ...");
	}
	void GameState_LoadingMenu::onLoadingDone(const CEGUI::EventArgs& /*e*/)
	{
		m_LoadingLabel->setProperty("Text", "DONE!");
		theEngine.getGameStateMachine().transition<GameState_MainMenu>();
	}

#pragma region IGameState_Implementation

	void GameState_LoadingMenu::handleEvent(const sf::Event& event)
	{
		if (theUI.handleEvent(event)) // GUI event will always come first
			return;
	}
	void GameState_LoadingMenu::render() const // called by a different thread, but .draw() takes const ref, so it should be fine
	{
// 		theUI.draw();
	}
	void GameState_LoadingMenu::update(float diff)
	{
		m_LoadingProgressbar->step();
	}
#pragma endregion
}