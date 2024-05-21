#pragma once
#include "Font.h"

#include <cstdint>
#include <memory>

namespace Pong {

	class Paddle;
	class Ball;

	class Renderer
	{
	public:
		Renderer(uint32_t inWidth, uint32_t inHeight);
		~Renderer();

		void Draw();

		void Clear(uint16_t inColor = 0x00);
		void ClearAndDraw(uint16_t inColor);

		void DrawPaddle(const Paddle& inPaddle, uint16_t inColor);
		void DrawBall(const Ball& inBall, uint32_t inColor);

		void DrawText(uint32_t inX, uint32_t inY, const char* inText, uint16_t inColor = 0xffff);
		void DrawPixel(uint32_t inX, uint32_t inY, uint16_t inColor = 0xffff);

	private:
		// Test if a pixel at coordinates (inX, inY) can be written to image data
		bool ClipPixel(int inX, int inY) const;

		const uint32_t mWidth;
		const uint32_t mHeight;

		uint16_t* mImageData = nullptr;
		uint8_t* mParallelLCDMemBase = nullptr;

		Font mFont;
	};

}