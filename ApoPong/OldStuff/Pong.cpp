#include "Pong.h"
// #include "Utils.h"

// #include "Menu/MainMenu.h"
// #include "Menu/GameUI.h"

#include <iostream>
#include <thread>

namespace Pong {

	Pong::Pong()
		: mRenderer(cWidth, cHeight), mLeftPaddle(30, 130), mRightPaddle(450, 130), mPeripherals()
	{ 
		// mMenu = std::make_shared<MainMenu>(*this);
	}

	Pong::~Pong()
	{
		// Clear to black
		mRenderer.ClearAndDraw(0x0);
	}

	void Pong::Run()
	{
		timespec loop_delay;
		loop_delay.tv_sec = 0;
		loop_delay.tv_nsec = 150 * 1000 * 1000;

		while (!mPeripherals.IsKnobPressed(Peripherals::Knob::Green))
		{
			mPeripherals.Update();

			// OnUpdate(1.0f);
			OnRender();

			// Idk, it was done in the example
			clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);

			// Though if we want to wait for 150ms than...
			using namespace std::chrono_literals;
			std::this_thread::sleep_for(150ms);
		}
	}

	void Pong::OnUpdate(float ts)
	{
		// mMenu->OnUpdate();

		if (mState == GameState::Menu)
			return;

		if (mState == GameState::WaitingToStart)
		{
			if (mPeripherals.IsKnobPressed(Peripherals::Knob::Green))
			{
				mBall.Launch();
			}
		}

		const uint32_t speed = 64;
		mLeftPaddle.Y = (mPeripherals.GetKnobDelta(Peripherals::Knob::Red) * cHeight) / speed;
		mRightPaddle.Y = (mPeripherals.GetKnobDelta(Peripherals::Knob::Blue) * cHeight) / speed;

		/*
		uint32_t paddle_speed = 3;

		if (Walnut::Input::IsKeyDown(Walnut::KeyCode::W))
			mLeftPaddle.Y -= paddle_speed;

		if (Walnut::Input::IsKeyDown(Walnut::KeyCode::S))
			mLeftPaddle.Y += paddle_speed;

		if (Walnut::Input::IsKeyDown(Walnut::KeyCode::Up))
			mRightPaddle.Y -= paddle_speed;

		if (Walnut::Input::IsKeyDown(Walnut::KeyCode::Down))
			mRightPaddle.Y += paddle_speed;
		*/

		// Keep the paddles in the arena
		// TODO: Clamp is inside Utils, remove everything from there regarding those enums
		mLeftPaddle.Y = Clamp(mLeftPaddle.Y, 0, cHeight - mLeftPaddle.GetHeight());
		mRightPaddle.Y = Clamp(mRightPaddle.Y, 0, cHeight - mRightPaddle.GetHeight());
		
		if (mBall.Overlaps(mLeftPaddle))
		{
			mBall.BounceOff(mLeftPaddle);
			mBounces++;
			mPointCounter++;
		}
		else if (mBall.Overlaps(mRightPaddle))
		{
			mBall.BounceOff(mRightPaddle);
			mBounces++;
			mPointCounter++;
		}

		if (HasModierAnyFlags(Modifier::AcceleratingBall))
		{
			if (mBounces == 3)
			{
				mBall.Accelerate();
				mBounces = 0;
			}
		}

		mBall.OnUpdate();

		if (mBall.GetX() < 0)
		{
			if (HasModierAnyFlags(Modifier::AdditivePointSystem))
				mRightScore += mPointCounter;
			else
				mRightScore++;

			ResetBoard();
		}
		else if (mBall.GetX() + Ball::cSize > cWidth)
		{
			if (HasModierAnyFlags(Modifier::AdditivePointSystem))
				mLeftScore += mPointCounter;
			else
				mLeftScore++;

			ResetBoard();
		}
	}

	void Pong::OnRender()
	{
		if (mState == GameState::Playing || mState == GameState::WaitingToStart)
		{
			mRenderer.Clear();

			mRenderer.DrawPaddle(mLeftPaddle, 0x001f);
			mRenderer.DrawPaddle(mRightPaddle, 0xf800);

			mRenderer.DrawBall(mBall, 0xffffffff);
		}
		else if (mState == GameState::Menu)
		{
			mRenderer.Clear(0xff00);

			// We would render ui here
		}
		mRenderer.Draw();
	}

	void Pong::StartGame()
	{
		mLeftScore = 0;
		mRightScore = 0;

		// mMenu = std::make_shared<GameUI>(*this);

		ResetBoard();
	}

	void Pong::SetModifier(Modifier inModifier, bool inEnable)
	{
		if (inEnable)
			mModifier |= inModifier;
		else
			mModifier &= ~inModifier;
	}

	void Pong::ResetBoard()
	{
		UpdateLedLine();

		mBall = Ball((cWidth - 2) / 2, (cHeight - 3)/ 2);

		mBounces = 0;
		mPointCounter = 1;

		mState = GameState::WaitingToStart;
	}

	void Pong::UpdateLedLine()
	{
		uint32_t value = 0;
		if (HasModierAnyFlags(Modifier::AdditivePointSystem))
		{
			for (uint32_t i = 0; i < mPointCounter; i++)
				value = (value << 1) | 1;
		}
		else
		{
			uint32_t left = 0;
			uint32_t right = 0;

			for (uint32_t i = 0; i < 16; i++)
			{
				if (i < mRightScore)
					right = (right << 1) | 1;
			}

			for (uint32_t i = 0; i < 16; i++)
			{
				if (i < mLeftScore)
					left = (left >> 1) | 0x80000000;
			}

			value = left | right;
		}

		mPeripherals.SetLedLine(value);
	}

}
