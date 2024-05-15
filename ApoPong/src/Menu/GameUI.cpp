#include "GameUI.h"

#include <cstdarg>

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

	GameUI::GameUI(Pong& inGame)
		: mGameRef(inGame)
	{}

	void GameUI::OnUpdate(Peripherals* inPeripherals)
	{}

	void GameUI::OnRender(Renderer& inRenderer)
	{
		std::string text = sStringFormat("%u/%u", mGameRef.GetLeftScore() / mGameRef.GetRightScore());
		inRenderer.DrawText(Pong::cWidth / 2, 20, text.c_str(), 0xffff);
	}

}
