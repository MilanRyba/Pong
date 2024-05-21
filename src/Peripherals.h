#pragma once

#include "../mz_apo/mzapo_phys.h"
#include "../mz_apo/mzapo_regs.h"

#include "cstdint"
#include <cstdint>
#include <sys/types.h>

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

        bool IsKnobPressed(Knob inColor) const;
        bool IsKnobDown(Knob inColor) const;
        int GetKnobPosition(Knob inColor) const;
        int GetKnobDelta(Knob inColor) const;

        void SetLedLine(uint32_t inValue);
        void SetRGBLeds(uint32_t inValue);

    private:
        void ResolvePressedEvents();

        uint8_t* mMemBase = nullptr;
        int mData = 0;

        // Knob positions range between 0 and 1280
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
