#pragma once
#include "Font.h"

#include <cstdint>
#include <memory>

namespace Pong {

	class Paddle;
	class Ball;

	/// Responsible for rendering pixels to the LCD display
	class Renderer
	{
	public:
		/// Constructor
		/// @param Width and height of the LCD display
		Renderer(uint32_t inWidth, uint32_t inHeight);

		/// Destructor
		~Renderer();

		/// Draw the current's image buffer contents to the LCD display
		void Draw();

		/// Clear the image buffer
		void Clear(uint16_t inColor = 0x00);

		/// Clear the image buffer and draw it to the LCD display
		void ClearAndDraw(uint16_t inColor);

		/// Draw a paddle
		void DrawPaddle(const Paddle& inPaddle, uint16_t inColor);

		/// Draw a ball
		void DrawBall(const Ball& inBall, uint16_t inColor);

		/// Draw a string in screen coordinates
		void DrawText(uint32_t inX, uint32_t inY, const char* inText, uint16_t inColor = 0xffff);

		/// Draw a single pixel
		void DrawPixel(uint32_t inX, uint32_t inY, uint16_t inColor = 0xffff);

	private:
		// Test if a pixel at coordinates (inX, inY) can be written to image buffer
		bool ClipPixel(int inX, int inY) const;

		const uint32_t mWidth;					///< Width of the LCD display
		const uint32_t mHeight;					///< Height of the LCD display

		uint16_t* mImageData = nullptr;
		uint8_t* mParallelLCDMemBase = nullptr;

		Font mFont;
	};

}