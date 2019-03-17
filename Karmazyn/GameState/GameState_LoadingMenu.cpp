#include "GameState_LoadingMenu.hpp"
#include <algorithm>
#include <Logger.hpp>
#include "../Globals.hpp"
#include "../GUIManager/GUIManager.hpp"

namespace Karmazyn
{
	GameState_LoadingMenu::GameState_LoadingMenu(GameEngine& engine) :
		IGameState(engine),
		theGUI(engine.getUIManager()),

		m_LoadingGUIRoot(nullptr), m_VersionLabel(nullptr), m_TippLabel(nullptr), m_LoadingLabel(nullptr), m_LoadingProgressbar(nullptr)
	{
		CEGUI::Window* root = CEGUI::System::getSingletonPtr()->getDefaultGUIContext().getRootWindow();
		m_LoadingGUIRoot = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(Settings::GUI::LoadingScreenLayoutName, "layouts");

		m_VersionLabel = m_LoadingGUIRoot->getChildElement("VersionLabel");
		m_VersionLabel->setProperty("Text", BuildVersion);

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

		root->addChild(m_LoadingGUIRoot);
	}
	GameState_LoadingMenu::~GameState_LoadingMenu()
	{
		theGUI.getWindowManager().destroyWindow(m_LoadingGUIRoot);
	}
#pragma region IGameState_Implementation

	void GameState_LoadingMenu::handleEvent(const sf::Event& event)
	{
		if (theGUI.handleEvent(event)) // GUI event will always come first
			return;
		
		switch (event.type)
		{
			case sf::Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == sf::Mouse::Button::Right)
				{
					theEngine.Stop();
				}
				break;
			}
		}
	}
	std::string GameState_LoadingMenu::determineTippText()
	{
		constexpr std::array<const char*, 2> LoadingScreenTipps = {
			"TODO: these tipps will need to be updated, once there is something to do, as they are pretty much just placeholders, showing the overall picture of the loading screen.",
			"Lorem ipsum doloret sit amet, menjünk dógozni."
		};
		return *Utility::getRandomElement(LoadingScreenTipps);
	}
	std::string GameState_LoadingMenu::determineLoadingText()
	{
		return std::string("LAL");
	}
	void GameState_LoadingMenu::onLoadingDone(const CEGUI::EventArgs& /*e*/)
	{
		theLog->info("LOADING DONE!");
	}
	void GameState_LoadingMenu::render() const // called by a different thread, but .draw() takes const ref, so it should be fine
	{
		theGUI.draw();
	}
	void GameState_LoadingMenu::update(float diff)
	{
		m_LoadingProgressbar->step();
	}
#pragma endregion
}