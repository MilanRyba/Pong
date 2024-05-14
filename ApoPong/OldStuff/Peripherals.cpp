#include "Peripherals.h"
#include <iostream>

namespace Pong {

    Peripherals::Peripherals()
    {
        std::cout << "Knob\n";
        mMemBase = (unsigned char*)map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
        if (!mMemBase)
        {
            std::cout << "[Knob] Failed to initialize mMemBase\n";
            exit(1);
        }            
    }

    void Peripherals::Update()
    {
        mData = *(volatile uint32_t*)(mMemBase + SPILED_REG_KNOBS_8BIT_o);
    }

    bool Peripherals::IsKnobPressed(Knob inColor)
    {
        // Should these be int or uint32_t?        
        switch (inColor)
        {
        case Knob::Red:         return mData & 0x80000000;
        case Knob::Green:       return mData & 0x40000000;
        case Knob::Blue:        return mData & 0x20000000;
        }

        std::cout << "[IsKnobPressed] Invalid Knob\n";
        return false;
    }

    int Peripherals::GetKnobDelta(Knob inColor)
    {
        switch (inColor)
        {
        case Knob::Red:         return (mData >> 16) & 0xff;
        case Knob::Green:       return (mData >> 8)  & 0xff;
        case Knob::Blue:        return  mData        & 0xff;
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