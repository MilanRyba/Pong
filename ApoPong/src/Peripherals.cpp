#include "Peripherals.h"
#include <cstdint>
#include <iostream>

namespace Pong {
    
    Peripherals::Peripherals()
    {
        std::cout << "Created Peripherals\n";
        mMemBase = (uint8_t*)map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
        if (!mMemBase)
        {
            std::cout << "[Knob] Failed to initialize mMemBase\n";
            exit(1);
        }
    }

    void Peripherals::Update()
    {
        mData = *(volatile uint32_t*)(mMemBase + SPILED_REG_KNOBS_8BIT_o);

        uint16_t red_position = (mData >> 16) & 0xff;
        uint16_t green_position = (mData >> 8) & 0xff;
        uint16_t blue_position = mData & 0xff;

        mRedDelta = red_position - mRedPosition;
        mGreenDelta = green_position - mGreenPosition;
        mBlueDelta = blue_position - mBluePosition;
        
        // TODO: Clamp the values between -1 and 1 (or better something higher like -5 and 5)

        mRedPosition = red_position;
        mGreenPosition = green_position;
        mBluePosition = blue_position;
    }

    bool Peripherals::IsKnobPressed(Knob inColor) const
    {
        switch (inColor)
        {
        case Knob::Red:         return mData & 0x4000000;
        case Knob::Green:       return mData & 0x2000000;
        case Knob::Blue:        return mData & 0x1000000;
        }

        std::cout << "[IsKnobPressed] Invalid Knob\n";
        return false;
    }

    int Peripherals::GetKnobPosition(Knob inColor) const
    {
        switch (inColor)
        {
        case Knob::Red:         return mRedPosition;
        case Knob::Green:       return mGreenPosition;
        case Knob::Blue:        return mBluePosition;
        }

        std::cout << "[GetKnobPosition] Invalid Knob\n";
        return 0;
    }

    int Peripherals::GetKnobDelta(Knob inColor) const
    {
        switch (inColor)
        {
        case Knob::Red:         return mRedDelta;
        case Knob::Green:       return mGreenDelta;
        case Knob::Blue:        return mBlueDelta;
        }

        std::cout << "[GetKnobDelta] Invalid Knob\n";
        return 0;
    }

    void Peripherals::SetLedLine(uint32_t inValue)
    {
        *(volatile uint32_t*)(mMemBase + SPILED_REG_LED_LINE_o) = inValue;
    }

    void Peripherals::SetRGBLeds(uint32_t inValue)
    {
        *(volatile uint32_t*)(mMemBase + SPILED_REG_LED_RGB1_o) = inValue;
    }

}