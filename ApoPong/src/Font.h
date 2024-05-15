#pragma once

namespace Pong {

	class Renderer;

	class Font
	{
	public:
		// Constructor
								Font() = default;

		// Create a font
		void					Create(Renderer* inRenderer);

		// Draw a string at a specific location
		void					DrawText(uint32_t inX, uint32_t inY, const char* inText, uint16_t inColor);

	private:
		void					DrawChar(uint32_t inX, uint32_t inY, char inChar, uint16_t inColor);
		void					DrawPixelBig(uint32_t inX, uint32_t inY, uint16_t inColor);
		int						CharWidth(int inChar) const;

		Renderer*				mRenderer;

		font_descriptor_t*		mDescriptor;
		uint32_t				mScale = 1;				// Scale of characters
		uint32_t				mSpacing = 1;			// Spacing between characters
	};

}