#pragma once
#include "Menu.h"
#include "../Pong.h"

#include <array>

namespace Pong {

	class ModifiersMenu : public Menu
	{
	public:
		ModifiersMenu(Pong& inGame);

		void OnUpdate(Peripherals* inPeripherals) override;
		void OnRender(Renderer& inRenderer) override;

	private:
		Pong& mGameRef;

		struct ModifierState
		{
			Modifier Mod = Modifier::None;
			bool Enabled = false;
		};

		std::array<ModifierState, 3> mModifiers;
		int mSelected = 0;
	};

}