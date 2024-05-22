#pragma once
#include "../Renderer.h"
#include "../Peripherals.h"

namespace Pong {

	/// Base class for a menu
	class Menu
	{
	public:
		/// Virtual destructor
		virtual ~Menu() = default;

		/// Update menu
		virtual void OnUpdate(Peripherals* inPeripherals) {}

		/// Render menu
		virtual void OnRender(Renderer& inRenderer) {}
	};

}