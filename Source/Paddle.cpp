#include "Paddle.h"

namespace Pong {

	bool Paddle::InsideHole(uint32_t inY)
	{
		uint32_t y = inY - Y;
		for (const Hole& hole : mHoles)
		{
			if (hole.Contains(y))
				return true;
		}
		return false;
	}

	void Paddle::CreateHole(uint32_t inY)
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

	void Paddle::MergeHoles()
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

}
