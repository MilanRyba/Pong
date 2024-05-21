#pragma once
#include <array>

#include "Menu.h"

#include "../Pong.h"

namespace Pong {

	class Pong;

	class MainMenu : public Menu
	{
	public:
		MainMenu(Pong& inGame);

		void OnUpdate(Peripherals* inPeripherals) override;
		void OnRender(Renderer& inRenderer) override;

	private:
		Pong& mGameRef;

		std::array<const char*, 3> mOptions = { "Play", "Modifiers", "Exit" };
		int mSelected = 0;
	};

}