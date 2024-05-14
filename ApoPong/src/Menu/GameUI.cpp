#include "GameUI.h"

namespace Pong {

	GameUI::GameUI(Pong& inGame)
		: mGameRef(inGame)
	{}

	void GameUI::OnUpdate(Peripherals* inPeripherals)
	{}

	void GameUI::OnRender(Renderer& inRenderer)
	{
		// At the top fo the screen...
		// mGameRef.GetLeftScore() / mGameRef.GetRightScore()
	}

}
