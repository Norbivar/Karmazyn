#include "UIState_MainMenu.hpp"

#include "../../GameState/MainMenu/GameState_MainMenu.hpp"
#include "../../GameState/Game/GameState_Game.hpp"

#include <Map/Map.hpp>

namespace Karmazyn
{
	UIState_MainMenu::UIState_MainMenu(UIManager& uimanager, GameState_MainMenu& gamestate) :
		IUIState{ uimanager },
		theGameState{ gamestate }
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
			m_OptionResolutionWidth = static_cast<CEGUI::Editbox*>(m_OptionsWindow->getChildElementRecursive("ResolutionWidth"));
			m_OptionResolutionWidth->setText(theConfig->getAsString<Configs::ResolutionX>());

			m_OptionResolutionHeight = static_cast<CEGUI::Editbox*>(m_OptionsWindow->getChildElementRecursive("ResolutionHeight"));
			m_OptionResolutionHeight->setText(theConfig->getAsString<Configs::ResolutionY>());

			std::string validation_regex = "[0-9]{1,4}"; 
			m_OptionResolutionWidth->setValidationString(validation_regex);
			m_OptionResolutionHeight->setValidationString(validation_regex);
		}
		m_OptionWindowedModeCheckbox = static_cast<CEGUI::ToggleButton*>(m_MainMenuRoot->getChildElementRecursive("WindowedModeCheckbox"));
		{
			const auto toggled = theConfig->get<Configs::RenderWindowStyle>() & sf::Style::Fullscreen;
			m_OptionWindowedModeCheckbox->setSelected(!toggled);
		}

		m_OptionVSyncCheckbox = static_cast<CEGUI::ToggleButton*>(m_MainMenuRoot->getChildElementRecursive("VSyncCheckbox"));
		{
			const auto toggled = theConfig->get<Configs::VSync>();
			m_OptionVSyncCheckbox->setSelected(toggled);
		}

		m_RestartNotificationLabel = static_cast<CEGUI::Window*>(m_OptionsWindow->getChildElement("RestartNotificationLabel"));
		m_RestartNotificationLabel->hide();
		#pragma endregion

		#pragma region WidgetEventSubscriptors
		m_NewGameButton->subscribeEvent(CEGUI::PushButton::EventClicked,  CEGUI::Event::Subscriber(&UIState_MainMenu::onNewGameClicked,  this));
		m_LoadGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&UIState_MainMenu::onLoadGameClicked, this));
		m_OptionsButton->subscribeEvent(CEGUI::PushButton::EventClicked,  CEGUI::Event::Subscriber(&UIState_MainMenu::onOptionsClicked,  this));
		m_QuitGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&UIState_MainMenu::onQuitGameClicked, this));


		CEGUI::Event::Subscriber resolutionChanged([&]()
		{
			auto width = boost::lexical_cast<unsigned int>(m_OptionResolutionWidth->getText().c_str());
			auto height = boost::lexical_cast<unsigned int>(m_OptionResolutionHeight->getText().c_str());
			theGameState.onChangeScreenSize(width, height);
			m_RestartNotificationLabel->show();
		});
		m_OptionResolutionWidth->subscribeEvent(CEGUI::Editbox::EventTextChanged,  resolutionChanged);
		m_OptionResolutionHeight->subscribeEvent(CEGUI::Editbox::EventTextChanged, resolutionChanged);

		// Handle VSYNC checking
		m_OptionVSyncCheckbox->subscribeEvent(CEGUI::ToggleButton::EventSelectStateChanged, CEGUI::Event::Subscriber([&]()
		{
			const auto newValue = m_OptionVSyncCheckbox->isSelected();
			theGameState.onVerticalSyncChanged(newValue);
			m_RestartNotificationLabel->show();
		}));
		// Handle WINDOWEDMODE checking
		m_OptionWindowedModeCheckbox->subscribeEvent(CEGUI::ToggleButton::EventSelectStateChanged, CEGUI::Event::Subscriber([&]()
		{
			const auto newValue = m_OptionWindowedModeCheckbox->isSelected();
			theGameState.onWindowedModeChanged(newValue);
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

	void UIState_MainMenu::onNewGameClicked(const CEGUI::EventArgs&)
	{
		theLog->info("NEW GAME CLICKED");
		Map testmap = Map::create<TestRandomGenerator>(150, 150, 1);
		testmap.print();

	}

	void UIState_MainMenu::onLoadGameClicked(const CEGUI::EventArgs&)
	{
		theLog->info("LOAD GAME CLICKED");
	}

	void UIState_MainMenu::onOptionsClicked(const CEGUI::EventArgs&)
	{
		if (m_OptionsWindow->isVisible())
			m_OptionsWindow->hide();
		else
			m_OptionsWindow->show();
	}

	void UIState_MainMenu::onQuitGameClicked(const CEGUI::EventArgs&)
	{
		theGameState.onQuitGameClicked();
	}


	void UIState_MainMenu::show()
	{
		m_MainMenuRoot->show();
		m_OptionsWindow->hide();

		m_MainMenuRoot->activate();
		
		theLog->info("Main Menu shown!");
	}

	void UIState_MainMenu::hide()
	{
		m_MainMenuRoot->deactivate();
		m_MainMenuRoot->hide();
	}
}