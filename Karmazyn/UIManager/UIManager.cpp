#include "UIManager.hpp"

#include "Engine.hpp"
#include "../Globals.hpp"

namespace Karmazyn
{
	UIManager::UIManager(Engine& engine) :
		theEngine       {engine},
		//pMyWindow(window),
		m_Renderer      {CEGUI::OpenGL3Renderer::bootstrapSystem()},
		m_System        {*CEGUI::System::getSingletonPtr()},
		m_WindowManager {*CEGUI::WindowManager::getSingletonPtr()}
	{
		try
		{
			m_Renderer.enableExtraStateSettings(true);
			// First set up the default directories that the CEGUI resource provider will use.
			CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*> (
				CEGUI::System::getSingleton().getResourceProvider());

			rp->setResourceGroupDirectory("schemes",    Settings::GUI::AssetsRootPath + "/schemes/");
			rp->setResourceGroupDirectory("imagesets",  Settings::GUI::AssetsRootPath + "/imagesets/");
			rp->setResourceGroupDirectory("fonts",      Settings::GUI::AssetsRootPath + "/fonts/");
			rp->setResourceGroupDirectory("layouts",    Settings::GUI::AssetsRootPath + "/layouts/");
			rp->setResourceGroupDirectory("looknfeels", Settings::GUI::AssetsRootPath + "/looknfeel/");

			CEGUI::Font::setDefaultResourceGroup("fonts");
			CEGUI::Scheme::setDefaultResourceGroup("schemes");
			CEGUI::WindowManager::setDefaultResourceGroup("layouts");
			CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
			CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");

			CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
			if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
			{
				parser->setProperty("SchemaDefaultResourceGroup", "schemas");
			}

			CEGUI::SchemeManager::getSingleton().createFromFile("WindowsLook.scheme", "schemes"); // Load the Main Menu Scheme.
			CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-10.font");  // Default font loading.
			m_System.getDefaultGUIContext().setDefaultFont("DejaVuSans-10");        // Default font loading.

			CEGUI::SchemeManager::getSingleton().createFromFile(Settings::GUI::SchemeName, "schemes"); // Load the Main Menu Scheme.

			// Setting default cursor to display.
			CEGUI::MouseCursor& cursor = m_System.getDefaultGUIContext().getMouseCursor();
			cursor.setDefaultImage("WindowsLook/MouseArrow");

			// First, the default, root window:
			CEGUI::Window* root = m_WindowManager.createWindow("DefaultWindow", "root");
			m_System.getDefaultGUIContext().setRootWindow(root);

			root->setMousePassThroughEnabled(true); // this will make the invisible root ignore mouse events so that they can be processed by the Game itself

			for (std::string layoutname : Settings::GUI::LayoutsToLoad)
			{
				auto* layout = m_WindowManager.loadLayoutFromFile(layoutname, "layouts");
				layout->hide();
				root->addChild(layout);
			}

			// TODO: set up the KeyboardInputTranslator as well when we actually have things that need input.
			theLog->info("CEGUI set up correctly!");
		}
		catch (const CEGUI::Exception& e)
		{
			theLog->error("GUIManager error: {}", e.getMessage().c_str());
			// TODO: throw further?
		}
	}
	bool UIManager::handleEvent(const sf::Event& ev)
	{
		switch (ev.type)
		{
			case sf::Event::MouseMoved:
			{
				m_System.getDefaultGUIContext().injectMousePosition(
					static_cast<float>(ev.mouseMove.x),
					static_cast<float>(ev.mouseMove.y)
				);
				return false; // infact, the game might (and probably will) have an outline for units/things under cursor, so indeed this should not block
			}

			case sf::Event::MouseButtonPressed:
			{
				const auto& mouse = m_InputTranslator.translateMouse(ev.mouseButton.button);
				return m_System.getDefaultGUIContext().injectMouseButtonDown(mouse); // this will only swallow the event if it was handled by the UI - I guess
			}
			case sf::Event::MouseButtonReleased:
			{
				const auto& mouse = m_InputTranslator.translateMouse(ev.mouseButton.button);
				return m_System.getDefaultGUIContext().injectMouseButtonUp(mouse);
			}
			case sf::Event::KeyPressed:
			{
				const auto& key = m_InputTranslator.translateKey(ev.key.code);
				return m_System.getDefaultGUIContext().injectKeyDown(key);
			}
			case sf::Event::TextEntered:
			{
				return m_System.getDefaultGUIContext().injectChar(ev.text.unicode);
			}
			case sf::Event::KeyReleased:
			{
				const auto& key = m_InputTranslator.translateKey(ev.key.code);
				return m_System.getDefaultGUIContext().injectKeyUp(key);
			}
			case sf::Event::Resized:
			{
				m_System.notifyDisplaySizeChanged({
						static_cast<float>(ev.size.width),
						static_cast<float>(ev.size.height)
					}
				);
				return false;
			}
		}
		return false; // every unhandled event will be passed to the GameEngine
	}
	void UIManager::handleNativeMouseMove(const sf::Vector2i& ev)
	{
		m_System.getDefaultGUIContext().injectMousePosition(
			static_cast<float>(ev.x),
			static_cast<float>(ev.y)
		);
	}
}