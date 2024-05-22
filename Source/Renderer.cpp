#include "Renderer.h"
#include "Ball.h"
#include "Paddle.h"

#include "../mz_apo/mzapo_parlcd.h"
#include "../mz_apo/mzapo_phys.h"
#include "../mz_apo/mzapo_regs.h"

#include <cstdint>
#include <iostream>

namespace Pong {

	Renderer::Renderer(uint32_t inWidth, uint32_t inHeight)
		: mWidth(inWidth), mHeight(inHeight)
	{
		mImageData = new uint16_t[mWidth * mHeight];
		mParallelLCDMemBase = (uint8_t*)map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);

		if (!mParallelLCDMemBase)
		{
			std::cout << "Failed to initialize mParallelLCDMemBase\n";
			exit(1);
		}

		parlcd_hx8357_init(mParallelLCDMemBase);

		mFont.Create(this);

		ClearAndDraw(0x0);
	}

	Renderer::~Renderer()
	{
		delete[] mImageData;
	}

	void Renderer::Draw()
	{
		parlcd_write_cmd(mParallelLCDMemBase, 0x2c);

		for (uint32_t i = 0; i < mWidth * mHeight; i++)
			parlcd_write_data(mParallelLCDMemBase, mImageData[i]);
	}

	void Renderer::Clear(uint16_t inColor)
	{
		for (uint32_t i = 0; i < mWidth * mHeight; i++)
			mImageData[i] = inColor;
	}

	void Renderer::ClearAndDraw(uint16_t inColor)
	{
		parlcd_write_cmd(mParallelLCDMemBase, 0x2c);

		for (uint32_t i = 0; i < mWidth * mHeight; i++)
		{
			mImageData[i] = inColor;
			parlcd_write_data(mParallelLCDMemBase, mImageData[i]);
		}
	}

	void Renderer::DrawPaddle(const Paddle& inPaddle, uint16_t inColor)
	{
		const std::vector<Paddle::Hole>& holes = inPaddle.GetHoles();

		for (uint32_t y = inPaddle.Y; y < inPaddle.Y + inPaddle.GetHeight(); y++)
		{
			for (const auto& hole : holes)
			{
				if (hole.GetMin() == y)
					y = hole.GetMax();
			}

			for (uint32_t x = inPaddle.GetX(); x < inPaddle.GetX() + inPaddle.GetWidth(); x++)
				DrawPixel(x, y, inColor);
		}
	}

	void Renderer::DrawBall(const Ball& inBall, uint16_t inColor)
	{
		for (int y = inBall.GetY(); y < inBall.GetY() + Ball::cSize; y++)
		{
			for (int x = inBall.GetX(); x < inBall.GetX() + Ball::cSize; x++)
				DrawPixel(x, y, inColor);
		}
	}

	void Renderer::DrawText(uint32_t inX, uint32_t inY, const char* inText, uint16_t inColor)
	{
		mFont.DrawText(inX, inY, inText, inColor);
	}

	void Renderer::DrawPixel(uint32_t inX, uint32_t inY, uint16_t inColor)
	{
		if (ClipPixel(inX, inY))
			return;

		mImageData[inX + inY * mWidth] = inColor;
	}

	bool Renderer::ClipPixel(int inX, int inY) const
	{
		return inX < 0 || inX >= mWidth || inY < 0 || inY >= mHeight;
	}

}
