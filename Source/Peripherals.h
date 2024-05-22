#pragma once

#include "../mz_apo/mzapo_phys.h"
#include "../mz_apo/mzapo_regs.h"

#include "cstdint"
#include <cstdint>
#include <sys/types.h>

namespace Pong {

    /// Peripherals interface class which keeps track on the status of all knobs and provides a way control the board's LED's
    class Peripherals
    {
    public:
        /// Constructor
        Peripherals();

        /// Update each of the peripherals on the board
        void Update();

        /// Enum to identify knob type
        enum class Knob
        {
            Red, Green, Blue
        };

        /// Checks if a knob is pressed or not
        bool IsKnobPressed(Knob inColor) const;

        /// Checks if a knob is being held down or not
        bool IsKnobDown(Knob inColor) const;

        /// Get knob's current position
        int GetKnobPosition(Knob inColor) const;

        /// Get knob's current change in position
        int GetKnobDelta(Knob inColor) const;

        /// Light up the LED line with a 32-bit number where each bit represent a single LED
        void SetLEDLine(uint32_t inValue);

        /// Set the color on two RGB LED's
        void SetRGBLEDs(uint32_t inValue);

    private:
        void ResolvePressedEvents();

        uint8_t* mMemBase = nullptr;
        int mData = 0;

        /// Knob positions range between 0 and 1280
        uint16_t mRedPosition = 0;
        uint16_t mGreenPosition = 0;
        uint16_t mBluePosition = 0;

        int8_t mRedDelta = 0;
        int8_t mGreenDelta = 0;
        int8_t mBlueDelta = 0;

        bool mRedDown = false;
        bool mGreenDown = false;
        bool mBlueDown = false;

        bool mRedPressed = false;
        bool mGreenPressed = false;
        bool mBluePressed = false;
    };

}
