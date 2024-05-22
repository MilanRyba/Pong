#include "GameUI.h"
#include "MainMenu.h"

#include <cstdarg>
#include <iostream>

namespace Pong {

	std::string sStringFormat(const char* inFMT, ...)
	{
		char buffer[1024];

		// Format the string
		va_list list;
		va_start(list, inFMT);
		vsnprintf(buffer, sizeof(buffer), inFMT, list);
		va_end(list);

		return std::string(buffer);
	}

	GameUI::GameUI(Application& inGame)
		: mGameRef(inGame)
	{}

	void GameUI::OnUpdate(Peripherals* inPeripherals)
	{
		if (inPeripherals->IsKnobPressed(Peripherals::Knob::Red) && inPeripherals->IsKnobPressed(Peripherals::Knob::Green))
			mGameRef.ReturnToMainMenu();

		if (inPeripherals->IsKnobPressed(Peripherals::Knob::Blue) && inPeripherals->IsKnobPressed(Peripherals::Knob::Green))
			mGameRef.ReturnToMainMenu();
	}

	void GameUI::OnRender(Renderer& inRenderer)
	{
		std::string text = sStringFormat("%u - %u", mGameRef.GetLeftScore(), mGameRef.GetRightScore());
		inRenderer.DrawText(Pong::cWidth / 2 - 30, 10, text.c_str(), 0xffff);
	}

}
