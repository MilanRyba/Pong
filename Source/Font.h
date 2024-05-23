#pragma once
#include "../mz_apo/font_types.h"

#include <cstdint>

namespace Pong {

	class Renderer;

	/// Font class, used to display text on the board's LCD display
	class Font
	{
	public:
		/// Constructor
		Font() = default;

		/// Create a font
		void Create(Renderer* inRenderer);

		/// Draw a string in screen coordinates
		void DrawText(uint32_t inX, uint32_t inY, const char* inText, uint16_t inColor);

	private:
		// Draw a single char
		void DrawChar(uint32_t inX, uint32_t inY, char inChar, uint16_t inColor);

		void DrawPixelBig(uint32_t inX, uint32_t inY, uint16_t inColor);
		int	CharWidth(int inChar) const;

		Renderer* mRenderer;

		font_descriptor_t* mDescriptor;
		uint32_t mScale = 1;				///< Scale of characters
	};

}
