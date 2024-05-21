#include "Font.h"
#include "Renderer.h"

#include <cstdint>

namespace Pong {

	void Font::Create(Renderer* inRenderer)
	{
        mRenderer = inRenderer;
        mDescriptor = &font_winFreeSystem14x16;
	}

    void Font::DrawText(uint32_t inX, uint32_t inY, const char* inText, uint16_t inColor)
    {
        for (uint32_t i = 0; inText[i] != '\0'; i++)
            DrawChar(inX + (mDescriptor->maxwidth + mSpacing) * i * mScale, inY, inText[i], inColor);
    }

	void Font::DrawChar(uint32_t inX, uint32_t inY, char inChar, uint16_t inColor)
	{
		int char_width = CharWidth(inChar);
		const font_bits_t* ptr;

		if ((inChar >= mDescriptor->firstchar) && (inChar - mDescriptor->firstchar < mDescriptor->size))
		{
			if (mDescriptor->offset)
			{
				ptr = &mDescriptor->bits[mDescriptor->offset[inChar - mDescriptor->firstchar]];
			}
			else
			{
				int bw = (mDescriptor->maxwidth + 15) / 16;
				ptr = &mDescriptor->bits[(inChar - mDescriptor->firstchar) * bw * mDescriptor->height];
			}
			
			for (uint32_t i = 0; i < mDescriptor->height; i++)
			{
				font_bits_t value = *ptr;
				for (int j = 0; j < char_width; j++)
				{
					if ((value & 0x8000) != 0)
						DrawPixelBig(inX + mScale * j, inY + mScale * i, inColor);

					value <<= 1;
				}
				ptr++;
			}
		}
	}

    void Font::DrawPixelBig(uint32_t inX, uint32_t inY, uint16_t inColor)
    {
        for (uint32_t i = 0; i < mScale; i++)
            for (uint32_t j = 0; j < mScale; j++)
                mRenderer->DrawPixel(inX + i, inY + j, inColor);
    }

    int Font::CharWidth(int inChar) const
    {
        if (!mDescriptor->width)
            return mDescriptor->maxwidth;
        else
            return mDescriptor->width[inChar - mDescriptor->firstchar];
    }

}
