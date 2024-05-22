#pragma once
#include "Menu.h"
#include "../Application.h"

#include <array>

namespace Pong {

	/// Menu showing the possible modifier options which can be toggled with a knob
	class ModifiersMenu : public Menu
	{
	public:
		/// Constructor
		ModifiersMenu(Application& inGame);

		void OnUpdate(Peripherals* inPeripherals) override;
		void OnRender(Renderer& inRenderer) override;

	private:
		Application& mGameRef;

		// Helper structure for managing modifier options
		struct ModifierState
		{
			Modifier Mod = Modifier::None;
			uint32_t Color = 0x0;
			bool Enabled = false;

			ModifierState() = default;
			ModifierState(Modifier inMod, uint32_t inColor, bool inEnabled) : Mod(inMod), Color(inColor), Enabled(inEnabled) {}
			ModifierState& operator = (ModifierState inRHS) { Mod = inRHS.Mod; Color = inRHS.Colorl; Enabled = inRHS.Enabled; return *this; }
		};

		std::array<ModifierState, 3> mModifiers;		///< List of all the modifier options
		int mSelected = 0;								///< Which option is currently selected
	};

}