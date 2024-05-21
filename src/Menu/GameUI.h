#pragma once
#include "Menu.h"

#include "../Pong.h"

#include <array>

namespace Pong {

	class GameUI : public Menu
	{
	public:
		GameUI(Pong& inGame);

		void OnUpdate(Peripherals* inPeripherals) override;
		void OnRender(Renderer& inRenderer) override;

	private:
		Pong& mGameRef;
	};

}