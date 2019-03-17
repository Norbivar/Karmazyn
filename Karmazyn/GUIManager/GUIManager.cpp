#include "GUIManager.hpp"
#include "../Globals.hpp"
#include <Logger.hpp>

namespace Karmazyn
{
	GUIManager::GUIManager(GameEngine& engine) :
		theEngine       (engine),
		//pMyWindow(window),
		m_Renderer      (CEGUI::OpenGLRenderer::bootstrapSystem()),
		m_System        (*CEGUI::System::getSingletonPtr()),
		m_WindowManager (*CEGUI::WindowManager::getSingletonPtr())
	{
		try
		{
			const auto& a = m_System.getDefaultGUIContext();

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
			cursor.show();

			// Now That CEGUI has been set up, we initialize the InputTranslators.
			m_MouseInputTranslator = {
				{ sf::Mouse::Button::Left,      CEGUI::MouseButton::LeftButton      },
				{ sf::Mouse::Button::Right,     CEGUI::MouseButton::RightButton     },
				{ sf::Mouse::Button::Middle,    CEGUI::MouseButton::MiddleButton    }
			};

			// First, the default, root window:
			CEGUI::Window* root = m_WindowManager.createWindow("DefaultWindow", "root");
			m_System.getDefaultGUIContext().setRootWindow(root);

			// TODO: set up the KeyboardInputTranslator as well when we actually have things that need input.
			theLog->info("CEGUI set up correctly!");
		}
		catch (const CEGUI::Exception& e)
		{
			theLog->error("GUIManager error: {}", e.getMessage().c_str());
			// TODO: throw further?
		}
	}
	bool GUIManager::handleEvent(const sf::Event& ev)
	{
		switch (ev.type)
		{
			case sf::Event::Resized:
			{
				m_System.notifyDisplaySizeChanged({
						static_cast<float>(ev.size.width),
						static_cast<float>(ev.size.height)
					}
				);
				return false;
			}

			case sf::Event::MouseMoved:
			{
				m_System.getDefaultGUIContext().injectMousePosition(
					ev.mouseMove.x,
					ev.mouseMove.y
				);
				return true; // Game should not be concerned with the mouse movement 
			}
			return false;
		}
	}
	void GUIManager::handleNativeMouseMove(const sf::Vector2i& ev)
	{
		m_System.getDefaultGUIContext().injectMousePosition(
			ev.x,
			ev.y
		);
	}
}