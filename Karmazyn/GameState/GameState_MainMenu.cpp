#include "GameState_MainMenu.hpp"
#include <Logger.hpp>

#include "ConfigList.hpp"
#include "../Globals.hpp"
#include "../GameEngine.hpp"
#include "../UIManager/UIManager.hpp"

namespace Karmazyn
{
	GameState_MainMenu::GameState_MainMenu(GameEngine& engine) :
		IGameState(engine),
		theUI(engine.getUIManager())
	{
		CEGUI::Window* root = CEGUI::System::getSingletonPtr()->getDefaultGUIContext().getRootWindow();
		m_MainMenuRoot = static_cast<CEGUI::Window*>(root->getChildElement("MenuBackgroundImage"));

		m_MainMenuWindow = m_MainMenuRoot->getChildElement("MainMenuWindow");
		{
			m_NewGameButton  = static_cast<CEGUI::PushButton*>(m_MainMenuWindow->getChildElement("NewGameButton"));
			m_NewGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameState_MainMenu::onNewGameClicked, this));

			m_LoadGameButton = static_cast<CEGUI::PushButton*>(m_MainMenuWindow->getChildElement("LoadGameButton"));
			m_LoadGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameState_MainMenu::onLoadGameClicked, this));

			m_OptionsButton  = static_cast<CEGUI::PushButton*>(m_MainMenuWindow->getChildElement("OptionsButton"));
			m_OptionsButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameState_MainMenu::onOptionsClicked, this));

			m_QuitGameButton = static_cast<CEGUI::PushButton*>(m_MainMenuWindow->getChildElement("QuitGameButton"));
			m_QuitGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameState_MainMenu::onQuitGameClicked, this));
		}

		m_OptionsWindow = static_cast<CEGUI::Window*>(m_MainMenuRoot->getChildElement("OptionsWindow"));
		{
			m_OptionVSyncCheckbox = static_cast<CEGUI::ToggleButton*>(m_MainMenuRoot->getChildElementRecursive("VSyncCheckbox"));
			//     OPTIONS modification:
			// Handle checkbox setting 
			{
				bool toggled = theConfig->get<bool>(Configs::VSync);
				m_OptionVSyncCheckbox->setSelected(toggled);
				m_OptionVSyncCheckbox->subscribeEvent(CEGUI::ToggleButton::EventSelectStateChanged, CEGUI::Event::Subscriber([&]()
				{
					bool newValue = m_OptionVSyncCheckbox->isSelected();
					theEngine.changeVerticalSynced(newValue);
					m_RestartNotificationLabel->show();
				}));
			}

			// OPTIONS end
			m_RestartNotificationLabel = static_cast<CEGUI::Window*>(m_OptionsWindow->getChildElement("RestartNotificationLabel"));
			m_RestartNotificationLabel->hide();

			// Handle close window button on Options Window
			m_OptionsWindow->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber([&]()
			{
				m_OptionsWindow->hide();
			}));
		}

		m_VersionLabel = m_MainMenuRoot->getChildElement("MenuVersionLabel");
		m_VersionLabel->setProperty("Text", BuildVersion);

		m_MainMenuRoot->show();
		m_OptionsWindow->hide();

		m_MainMenuRoot->activate();
	}

	GameState_MainMenu::~GameState_MainMenu()
	{
		theUI.getWindowManager().destroyWindow(m_MainMenuRoot);
	}

	void GameState_MainMenu::onNewGameClicked(const CEGUI::EventArgs &)
	{
		theLog->info("NEW GAME CLICKED");
	}
	void GameState_MainMenu::onLoadGameClicked(const CEGUI::EventArgs &)
	{
		theLog->info("LOAD GAME CLICKED");
	}
	void GameState_MainMenu::onOptionsClicked(const CEGUI::EventArgs &)
	{
		if(m_OptionsWindow->isVisible())
			m_OptionsWindow->hide();
		else
			m_OptionsWindow->show();
	}
	void GameState_MainMenu::onQuitGameClicked(const CEGUI::EventArgs &)
	{
		theEngine.Stop();
	}

	void GameState_MainMenu::update(float diff)
	{

	}

	void GameState_MainMenu::render() const
	{
// 		theUI.draw();
	}

	void GameState_MainMenu::handleEvent(const sf::Event& event)
	{
		if (theUI.handleEvent(event)) // GUI event will always come first
			return;
	}
}