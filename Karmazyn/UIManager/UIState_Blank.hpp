#pragma once

#include "IUIState.hpp"

namespace Karmazyn
{
	class UIState_Blank : public IUIState
	{
	public:
		UIState_Blank(UIManager& uimanager) : IUIState(uimanager) {}
		~UIState_Blank() override { }

	};
}