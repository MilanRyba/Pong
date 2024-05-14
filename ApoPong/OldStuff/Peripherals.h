#pragma once

#include "../mz_apo/mzapo_phys.h"
#include "../mz_apo/mzapo_regs.h"

#include <cstdint>

namespace Pong {

	class Peripherals
	{
	public:
		Peripherals();
		void Update();

		enum class Knob
		{
			Red, Green, Blue
		};

        bool IsKnobPressed(Knob inColor);

		// TODO: Delta isn't the best name
		int GetKnobDelta(Knob inColor);

		void SetLedLine(uint32_t inValue);
		void SetRGBLeds(uint32_t inValue);

	private:
		uint8_t* mMemBase = nullptr;
		int mData = 0;
	};

}