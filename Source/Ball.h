#pragma once
#include <cstdint>
#include <random>

namespace Pong {

	class Paddle;

	/// Contains the structure of a ball
	class Ball
	{
	public:
		/// Constructor
		Ball() = default;
		Ball(int inX, int inY);

		/// Update ball's position
		void OnUpdate();

		/// Launch the ball in a random direction from the starting position
		void Launch();

		/// Increase ball speed
		void Accelerate();

		/// Test if the ball overlaps with a paddle
		/// @param inAttrition Whether or not the 'Attrition' modifier is enabled
		bool Overlaps(Paddle& inPaddle, bool inAttrition);

		/// Bounce the ball off of a paddle
		void BounceOff(const Paddle& inPaddle);

		/// Getters
		inline int GetX() const { return mX; }
		inline int GetY() const { return mY; }

		constexpr static uint32_t cSize = 5;		///< Ball size in pixels

	private:
		int mX;										///< X position
		int mY;										///< Y position

		int mDeltaX = 0;							///< Movement in pixels over the x-axis for the next frame
		int mDeltaY = 0;							///< Movement in pixels over the y-axis for the next frame

		uint32_t mSpeed = 7;						///< Ball Speed
		uint32_t mAdditiveSpeed = 0;
		bool mShouldNotCollide = false;				///< Disables any ball collision when set to true
	};

}
