#pragma once
#include <cstdint>
#include <vector>

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
			for (const Hole& hole : mHoles)
			{
				if (hole.Contains(y))
					return true;
			}
			return false;
		}

		void CreateHole(uint32_t inY)
		{
			uint32_t y = inY - Y;
			Hole new_hole(y - 2, y + 2);

			if (mHoles.empty())
			{
				mHoles.push_back(new_hole);
				return;
			}

			bool collision = false;
			for (Hole& hole : mHoles)
			{
				if (hole.Overlaps(new_hole) || hole.Touches(new_hole))
				{
					hole.Encapsulate(new_hole);
					collision = true;
					break;
				}
			}

			if (collision)
				MergeHoles();
			else
				mHoles.push_back(new_hole);
		}

		uint32_t GetX() const { return mX; }
		uint32_t GetWidth() const { return mWidth; }
		uint32_t GetHeight() const { return mHeight; }

		uint32_t Y;						// Position of the top side

	private:
		const uint32_t mX;				// Position of the left side
		const uint32_t mWidth = 6;
		const uint32_t mHeight = 50;

		struct Hole
		{
			uint32_t Min;
			uint32_t Max;

			Hole(uint32_t inMin, uint32_t inMax) : Min(inMin), Max(inMax) {}

			bool Overlaps(const Hole& inOther) const
			{
				return !(Min > inOther.Max || Max < inOther.Min);
			}

			bool Touches(const Hole& inOther) const
			{
				return (Min - 1 == inOther.Max) || (Max + 1 == inOther.Min);
			}

			void Encapsulate(const Hole& inRHS)
			{
				Min = std::min(Min, inRHS.Min);
				Max = std::max(Max, inRHS.Max);
			}

			bool Contains(const uint32_t inPoint) const
			{
				return Min <= inPoint && Max >= inPoint;
			}
		};

		void MergeHoles()
		{
			for (int i = 0; i < mHoles.size(); i++)
			{
				Hole& hole1 = mHoles[i];
				for (int j = i + 1; j < mHoles.size(); j++)
				{
					Hole& hole2 = mHoles[j];

					if (hole1.Overlaps(hole2) || hole1.Touches(hole2))
					{
						hole1.Encapsulate(hole2);
						mHoles.erase(mHoles.begin() + j);
					}
				}
			}
		}

	public:
		std::vector<Hole> mHoles;
	};

}
