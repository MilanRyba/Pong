#pragma once
#include "../Renderer.h"

namespace Pong {

	class Menu
	{
	public:
		virtual ~Menu() = default;

		virtual void OnUpdate(Peripherals* inPeripherals) {}
		virtual void OnRender(Renderer& inRenderer) {}
	};

}