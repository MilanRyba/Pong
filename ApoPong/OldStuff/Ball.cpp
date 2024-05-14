#include "Ball.h"
#include "Pong.h"

#include "Walnut/Application.h"

#include <iostream>

namespace Pong {

	static constexpr float PI = 3.14159265358979323846f;
	static constexpr float Deg2Rad = PI / 180.0f;
	static constexpr float Rad2Deg = 180.0f / PI;

	Ball::Ball(int inX, int inY)
		: mX(inX), mY(inY)
	{
		mAdditiveSpeed = 0;
	}

	void Ball::OnUpdate()
	{
		// Wall collisions
		if (mY + mDeltaY < 0 || mY + cSize + mDeltaY >= Pong::cHeight)
		{
			mDeltaY *= -1;
		}

		mX += mDeltaX;
		mY += mDeltaY;
	}

	void Ball::Launch()
	{
		float seed = Walnut::Application::Get().GetTime();
		std::default_random_engine random(seed);

		std::uniform_int_distribution<int> dir_dist(0, 1);
		int direction = dir_dist(random) == 0 ? -1 : 1;

		std::uniform_real_distribution<float> angle_dist(-50.0f, 50.0f);
		float angle = angle_dist(random);

		// Prevent angles that are between [-20, 20]
		const float dead_zone = 20.0f;
		if (angle < 0.0f && angle > -dead_zone)
			angle = -dead_zone;

		if (angle > 0.0f && angle < dead_zone)
			angle = dead_zone;

		if (direction == -1)
			angle = 180.0f - angle;

		mDeltaX = (float)mSpeed * cos(angle * Deg2Rad);
		mDeltaY = (float)mSpeed * sin(angle * Deg2Rad);

		mDeltaX += (mDeltaX < 0 ? -1 : 1) * mAdditiveSpeed;
		mDeltaY += (mDeltaY < 0 ? -1 : 1) * mAdditiveSpeed;
	}

	void Ball::Accelerate()
	{
		std::cout << "Accelerated\n";
		mAdditiveSpeed++;

		mDeltaX += mDeltaX < 0 ? -1 : 1;
		mDeltaY += mDeltaY < 0 ? -1 : 1;
	}

	bool Ball::Overlaps(const Paddle& inPaddle)
	{
		// Check if the ball is above or below the paddle
		if (mY + cSize < inPaddle.Y || mY > inPaddle.Y + inPaddle.GetHeight())
			return false;
		
		if (inPaddle.GetX() < Pong::cWidth / 2)
		{
			// Left paddle
			uint32_t paddle_x = inPaddle.GetX() + inPaddle.GetWidth();
			if (mX < paddle_x && mX + cSize > paddle_x)
			{
				// Move the ball out of the paddle
				mX += paddle_x - mX;
				return true;
			}
		}
		else
		{
			// Right paddle
			if (mX < inPaddle.GetX() && mX + cSize > inPaddle.GetX())
			{
				// Move the ball out of the paddle
				mX -= mX + cSize - inPaddle.GetX();
				return true;
			}
		}

		return false;
	}

	void Ball::BounceOff(const Paddle& inPaddle)
	{
		float seed = Walnut::Application::Get().GetTime();
		std::default_random_engine random(seed);

		std::uniform_int_distribution<int> bounce_dir(0, 10);
		int bounce = bounce_dir(random);

		if (bounce < 5)
		{
			mDeltaX = -mDeltaX;
			std::cout << "--- NORMAL ---\n";
		}
		else if (bounce >= 5 && bounce < 8)
		{
			std::uniform_real_distribution<float> angle_dist(-50.0f, 50.0f);
			float angle = angle_dist(random);

			// Prevent angles that are between [-20, 20]
			const float dead_zone = 20.0f;
			if (angle < 0.0f && angle > -dead_zone)
				angle = -dead_zone;

			if (angle > 0.0f && angle < dead_zone)
				angle = dead_zone;

			if (mDeltaX > 0)
				angle = 180.0f - angle;

			mDeltaX = (float)mSpeed * cos(angle * Deg2Rad);
			mDeltaY = (float)mSpeed * sin(angle * Deg2Rad);

			mDeltaX += (mDeltaX < 0 ? -1 : 1) * mAdditiveSpeed;
			mDeltaY += (mDeltaY < 0 ? -1 : 1) * mAdditiveSpeed;

			std::cout << "::: RANDOM :::\n";
		}
		else
		{
			mDeltaX = -mDeltaX;
			mDeltaY = -mDeltaY;

			std::cout << "/// OPPOSITE ///\n";
		}
	}

}
