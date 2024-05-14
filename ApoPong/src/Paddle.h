#pragma once
#include <cstdint>

namespace Pong {

	class Paddle
	{
	public:
		Paddle(uint32_t inX, uint32_t inY) : mX(inX), Y(inY) {}

		void Reset()
		{
			mHoles.clear();
		}

		bool InsideHole(uint32_t inY)
		{
			uint32_t y = inY - Y;
			bool inside = false;

			for (uint32_t hole : mHoles)
				inside |= hole - 2 < y && hole + 2 > y;

			return inside;
		}

		void CreateHole(uint32_t inY)
		{
			// Go through all holes and find if this one overlaps any
			// If not, push back a new hole
			// If yes, extend the first we found check for collisions with other holes in that direction

			mHoles.push_back(inY - Y);
		}

		uint32_t GetX() const { return mX; }
		uint32_t GetWidth() const { return mWidth; }
		uint32_t GetHeight() const { return mHeight; }

		uint32_t Y;						// Position of the top side

	private:
		const uint32_t mX;				// Position of the left side
		const uint32_t mWidth = 6;
		const uint32_t mHeight = 50;

		// Make this 8 bit and each int will represent a single pixel, thus we can create a array of 50 int's
		std::vector<uint32_t> mHoles;
	};

}