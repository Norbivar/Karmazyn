#pragma once

namespace Karmazyn
{
	class UIManager; 

	class IUIState
	{
	public:
		explicit IUIState(UIManager& uimanager);
		virtual ~IUIState() { }

	protected:
		UIManager& theUI;
	};
}