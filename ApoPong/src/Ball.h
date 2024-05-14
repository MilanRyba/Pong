#pragma once
#include <cstdint>
#include <random>

namespace Pong {

	class Paddle;

	class Ball
	{
	public:
		Ball() = default;
		Ball(int inX, int inY);

		void OnUpdate();

		void Launch();
		void Accelerate();

		bool Overlaps(Paddle& inPaddle, bool inAttrition);
		void BounceOff(const Paddle& inPaddle);

		inline int GetX() const { return mX; }
		inline int GetY() const { return mY; }

		constexpr static uint32_t cSize = 5;

	private:
		int mX; // Ball x position
		int mY; // Ball y position

		int mDeltaX = 0; // Movement in pixels over the x-axis for the next frame
		int mDeltaY = 0; // Movement in pixels over the y-axis for the next frame

		uint32_t mSpeed = 20;
		uint32_t mAdditiveSpeed = 0;
		
	};

}