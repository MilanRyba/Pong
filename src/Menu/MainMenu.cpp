#include "MainMenu.h"
#include "ModifiersMenu.h"

#include "../Pong.h"
#include "../Utils.h"

#include <iostream>

namespace Pong {

	MainMenu::MainMenu(Pong& inGame)
		: mGameRef(inGame)
	{}

	void MainMenu::OnUpdate(Peripherals* inPeripherals)
	{
		mSelected += inPeripherals->GetKnobDelta(Peripherals::Knob::Blue);
		mSelected %= 3;

		if (inPeripherals->IsKnobPressed(Peripherals::Knob::Blue))
		{
			if (mSelected == 0)
				mGameRef.StartGame();

			if (mSelected == 1)
				mGameRef.SetMenu<ModifiersMenu>();

			if (mSelected == 2)
				mGameRef.Close();
		}
	}

	void MainMenu::OnRender(Renderer& inRenderer)
	{
		const uint32_t y_offset = 60;
		for (int i = 0; i < mOptions.size(); i++)
		{
			if (mSelected == i)
				inRenderer.DrawText(30, 10 + i * 60, mOptions[i], 0xffff);
			else
				inRenderer.DrawText(30, 10 + i * 60, mOptions[i], 0xf0f0);
		}
	}

}
