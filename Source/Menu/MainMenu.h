#pragma once
#include <array>

#include "Menu.h"

#include "../Application.h"

namespace Pong {

	class Application;

	class MainMenu : public Menu
	{
	public:
		/// Constructor
		MainMenu(Application& inGame);

		void OnUpdate(Peripherals* inPeripherals) override;
		void OnRender(Renderer& inRenderer) override;

	private:
		Application& mGameRef;

		std::array<const char*, 3> mOptions = { "Play", "Modifiers", "Exit" }; ///< List of all options
		int mSelected = 0;								///< Which option is currently selected
	};

}