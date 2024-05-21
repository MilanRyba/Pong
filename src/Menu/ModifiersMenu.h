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
			uint32_t Color = 0x0;
			bool Enabled = false;

			ModifierState() = default;
			ModifierState(Modifier inMod, uint32_t inColor, bool inEnabled) : Mod(inMod), Color(inColor), Enabled(inEnabled) {}
			ModifierState& operator = (ModifierState inRHS) { Mod = inRHS.Mod; Color = inRHS.Colorl; Enabled = inRHS.Enabled; return *this; }
		};

		std::array<ModifierState, 3> mModifiers;
		int mSelected = 0;
	};

}