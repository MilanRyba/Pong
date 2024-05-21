#pragma once
#include <cstdint>
#include <vector>

namespace Pong {

	class Paddle
	{
	public:
		// Constructor
		Paddle(uint32_t inX, uint32_t inY) : mX(inX), Y(inY) {}

		// Remove all holes
		void Reset() { mHoles.clear(); }

		// Test if ball is inside a hole
		bool InsideHole(uint32_t inY);

		void CreateHole(uint32_t inY);

		uint32_t GetX() const { return mX; }
		uint32_t GetWidth() const { return mWidth; }
		uint32_t GetHeight() const { return mHeight; }

		uint32_t Y;										// Position of the top side

		struct Hole
		{
			uint32_t Min;
			uint32_t Max;

			Hole(uint32_t inMin, uint32_t inMax) : Min(inMin), Max(inMax) {}

		private:
			// Check if this hole overlaps another hole
			bool Overlaps(const Hole& inOther) const
			{
				return !(Min > inOther.Max || Max < inOther.Min);
			}

			// Check if this hole lies next to another hole
			bool Touches(const Hole& inOther) const
			{
				return (Min - 1 == inOther.Max) || (Max + 1 == inOther.Min);
			}

			// Check if a point is inside this hole
			bool Contains(const uint32_t inPoint) const
			{
				return Min <= inPoint && Max >= inPoint;
			}

			// Encapsulate hole in hole
			void Encapsulate(const Hole& inRHS)
			{
				Min = std::min(Min, inRHS.Min);
				Max = std::max(Max, inRHS.Max);
			}
		};

		const std::vector<Hole>& GetHoles() const { return mHoles; }

	private:
		const uint32_t mX;								// Position of the left side
		const uint32_t mWidth = 6;						// Width of the paddle
		const uint32_t mHeight = 50;					// Height of the paddle

		// Go through all holes and merge those that overlap or touch
		void MergeHoles();

		std::vector<Hole> mHoles;
	};

}
