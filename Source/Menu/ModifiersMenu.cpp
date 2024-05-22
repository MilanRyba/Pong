#include "ModifiersMenu.h"
#include "MainMenu.h"

#include "../Utils.h"

namespace Pong {

	static const char* sGetModifierName(Modifier inModifier)
	{
		switch (inModifier)
		{
		case Modifier::None:					return "None";
		case Modifier::AcceleratingBall:		return "Accelerating Ball";
		case Modifier::AdditivePointSystem:		return "Additive Point System";
		case Modifier::Attrition:				return "Attrition";
		default:								return "";
		}
	}

	ModifiersMenu::ModifiersMenu(Application& inGame)
		: mGameRef(inGame)
	{
		mModifiers[0] = { Modifier::AdditivePointSystem, 0xff2a5580, false };
		mModifiers[1] = { Modifier::AcceleratingBall, 0xff802a55, false };
		mModifiers[2] = { Modifier::Attrition, 0xff55802a, false };
	}

	void ModifiersMenu::OnUpdate(Peripherals* inPeripherals)
	{
		mSelected += inPeripherals->GetKnobDelta(Peripherals::Knob::Blue);
		mSelected %= 3;

		// Select a modifier
		if (inPeripherals->IsKnobPressed(Peripherals::Knob::Blue))
		{
			ModifierState& state = mModifiers[mSelected];
			state.Enabled = state.Enabled ? false : true;
			mGameRef.SetModifier(state.Mod, state.Enabled);
		}

		// Return to Main Menu
		if (inPeripherals->IsKnobPressed(Peripherals::Knob::Red))
			mGameRef.SetMenu<MainMenu>();
	}

	void ModifiersMenu::OnRender(Renderer& inRenderer)
	{
		const uint32_t y_offset = 60;
		for (int i = 0; i < mModifiers.size(); i++)
		{
			const ModifierState& mod = mModifiers[i];
			uint32_t x = mSelected == i ? 50 : 30;
			uint16_t color = mod.Enabled ? 0xffff : 0xf0f0;

			inRenderer.DrawText(x, 10 + i * 60, sGetModifierName(mod.Mod), color);
		}
	}

}