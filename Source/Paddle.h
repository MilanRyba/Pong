#pragma once
#include <cstdint>
#include <vector>

namespace Pong {

	/// Contains the structure of a paddle
	class Paddle
	{
	public:
		/// Constructor
		Paddle(uint32_t inX, uint32_t inY) : mX(inX), Y(inY) {}

		/// Remove all holes from paddle
		void Reset() { mHoles.clear(); }

		/// Test if ball is inside a hole
		bool InsideHole(uint32_t inY);

		/// Create a new hole inside the paddle
		void CreateHole(uint32_t inY);

		uint32_t GetX() const { return mX; }
		uint32_t GetWidth() const { return mWidth; }
		uint32_t GetHeight() const { return mHeight; }

		/// Y position of paddle's top side
		uint32_t Y;

		/// Data structure for dealing with holes inside paddles
		struct Hole
		{
			/// Constructor
			Hole(uint32_t inMin, uint32_t inMax) : mMin(inMin), mMax(inMax) {}

			/// Get holes's upper bound
			uint32_t GetMin() const { return mMin; }

			/// Get holes's lower bound
			uint32_t GetMax() const { return mMax; }
			
			// Check if this hole overlaps another hole
			bool Overlaps(const Hole& inOther) const
			{
				return !(mMin > inOther.mMax || mMax < inOther.mMin);
			}

			// Check if this hole lies next to another hole
			bool Touches(const Hole& inOther) const
			{
				return (mMin - 1 == inOther.mMax) || (mMax + 1 == inOther.mMin);
			}

			// Check if a point is inside this hole
			bool Contains(const uint32_t inPoint) const
			{
				return mMin <= inPoint && mMax >= inPoint;
			}

			// Encapsulate hole in hole
			void Encapsulate(const Hole& inRHS)
			{
				mMin = std::min(mMin, inRHS.mMin);
				mMax = std::max(mMax, inRHS.mMax);
			}

			/// Holes min and max
			uint32_t mMin;
			uint32_t mMax;
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
