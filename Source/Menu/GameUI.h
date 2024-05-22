#pragma once
#include "Menu.h"

#include "../Application.h"

#include <array>

namespace Pong {

	/// UI that displays game score during gameplay
	class GameUI : public Menu
	{
	public:
		/// Constructor
		GameUI(Application& inGame);

		void OnUpdate(Peripherals* inPeripherals) override;
		void OnRender(Renderer& inRenderer) override;

	private:
		Application& mGameRef;
	};

}