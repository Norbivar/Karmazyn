#include "GameState_MainMenu.hpp"
#include <Logger.hpp>

#include "ConfigList.hpp"
#include "../../Globals.hpp"
#include "../../Engine.hpp"
#include "../../UIManager/UIManager.hpp"
#include "../../GameStateMachine.hpp"

#include "../Game/GameState_Game.hpp"

namespace Karmazyn
{
	GameState_MainMenu::GameState_MainMenu(Engine& engine) :
		IGameState(engine),
		theUI(engine.getUIManager())
	{
		CEGUI::Window* root = CEGUI::System::getSingletonPtr()->getDefaultGUIContext().getRootWindow();


		#pragma region WidgetInitializations
		m_MainMenuRoot = static_cast<CEGUI::Window*>(root->getChildElement("MenuBackgroundImage")); 

		m_MainMenuWindow = m_MainMenuRoot->getChildElement("MainMenuWindow");

		m_NewGameButton = static_cast<CEGUI::PushButton*>(m_MainMenuWindow->getChildElement("NewGameButton"));
		m_LoadGameButton = static_cast<CEGUI::PushButton*>(m_MainMenuWindow->getChildElement("LoadGameButton"));
		m_OptionsButton = static_cast<CEGUI::PushButton*>(m_MainMenuWindow->getChildElement("OptionsButton"));
		m_QuitGameButton = static_cast<CEGUI::PushButton*>(m_MainMenuWindow->getChildElement("QuitGameButton"));

		m_OptionsWindow = static_cast<CEGUI::Window*>(m_MainMenuRoot->getChildElement("OptionsWindow"));

		{
			std::string validation_regex = "[0-9]{1,4}"; 
			m_OptionResolutionWidth = static_cast<CEGUI::Editbox*>(m_OptionsWindow->getChildElementRecursive("ResolutionWidth"));
			m_OptionResolutionWidth->setText(theConfig->get<std::string>(Configs::ResolutionX));

			m_OptionResolutionHeight = static_cast<CEGUI::Editbox*>(m_OptionsWindow->getChildElementRecursive("ResolutionHeight"));
			m_OptionResolutionHeight->setText(theConfig->get<std::string>(Configs::ResolutionY));

			m_OptionResolutionWidth->setValidationString(validation_regex);
			m_OptionResolutionHeight->setValidationString(validation_regex);
		}
		m_OptionWindowedModeCheckbox = static_cast<CEGUI::ToggleButton*>(m_MainMenuRoot->getChildElementRecursive("WindowedModeCheckbox"));
		{
			const auto toggled = theConfig->get<int>(Configs::RenderWindowStyle);
			m_OptionWindowedModeCheckbox->setSelected(!(toggled & sf::Style::Fullscreen));
		}

		m_OptionVSyncCheckbox = static_cast<CEGUI::ToggleButton*>(m_MainMenuRoot->getChildElementRecursive("VSyncCheckbox"));
		{
			const auto toggled = theConfig->get<bool>(Configs::VSync);
			m_OptionVSyncCheckbox->setSelected(toggled);
		}

		m_RestartNotificationLabel = static_cast<CEGUI::Window*>(m_OptionsWindow->getChildElement("RestartNotificationLabel"));
		m_RestartNotificationLabel->hide();
		#pragma endregion

		#pragma region WidgetEventSubscriptors
		m_NewGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameState_MainMenu::onNewGameClicked, this));
		m_LoadGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameState_MainMenu::onLoadGameClicked, this));
		m_OptionsButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameState_MainMenu::onOptionsClicked, this));
		m_QuitGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameState_MainMenu::onQuitGameClicked, this));


		CEGUI::Event::Subscriber resolutionChanged([&]()
		{
			auto width = boost::lexical_cast<unsigned int>(m_OptionResolutionWidth->getText().c_str());
			auto height = boost::lexical_cast<unsigned int>(m_OptionResolutionHeight->getText().c_str());
			theEngine.changeScreenSize(width, height);
			m_RestartNotificationLabel->show();
		});
		m_OptionResolutionWidth->subscribeEvent(CEGUI::Editbox::EventTextChanged,  resolutionChanged);
		m_OptionResolutionHeight->subscribeEvent(CEGUI::Editbox::EventTextChanged, resolutionChanged);

		// Handle VSYNC checking
		m_OptionVSyncCheckbox->subscribeEvent(CEGUI::ToggleButton::EventSelectStateChanged, CEGUI::Event::Subscriber([&]()
		{
			const auto newValue = m_OptionVSyncCheckbox->isSelected();
			theEngine.changeVerticalSynced(newValue);
			m_RestartNotificationLabel->show();
		}));
		// Handle WINDOWEDMODE checking
		m_OptionWindowedModeCheckbox->subscribeEvent(CEGUI::ToggleButton::EventSelectStateChanged, CEGUI::Event::Subscriber([&]()
		{
			const auto newValue = m_OptionWindowedModeCheckbox->isSelected();
			theEngine.changeWindowedMode(newValue);
			m_RestartNotificationLabel->show();
		}));
		//Handle close window button on Options Window
		m_OptionsWindow->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked, CEGUI::Event::Subscriber([&]()
		{
			m_OptionsWindow->hide();
		}));

		#pragma endregion

		m_VersionLabel = m_MainMenuRoot->getChildElement("MenuVersionLabel");
		m_VersionLabel->setProperty("Text", Constants::BuildVersion);
	}

	GameState_MainMenu::~GameState_MainMenu()
	{
		
	}

	void GameState_MainMenu::onNewGameClicked(const CEGUI::EventArgs &)
	{
		theLog->info("NEW GAME CLICKED");
		theEngine.getGameStateMachine().transition<GameState_Game>(6);
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
#pragma region IGameState_Implementation
	void GameState_MainMenu::update(float diff)
	{

	}

	void GameState_MainMenu::render() const
	{
		theUI.draw();
	}

	void GameState_MainMenu::handleEvent(const sf::Event& event)
	{
		if (theUI.handleEvent(event)) // GUI event will always come first
			return;
	}
	void GameState_MainMenu::afterTransitionedIn()
	{
		m_MainMenuRoot->show();
		m_OptionsWindow->hide();

		m_MainMenuRoot->activate();
	}
	void GameState_MainMenu::beforeTransitionedOut()
	{
		m_MainMenuRoot->deactivate();
		m_MainMenuRoot->hide();
	}
#pragma endregion
}