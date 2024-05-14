#include "Pong.h"
#include "Peripherals.h"
#include "Utils.h"

#include "Menu/MainMenu.h"
#include "Menu/GameUI.h"

#include <iostream>

namespace Pong {

	Pong::Pong()
		: mRenderer(cWidth, cHeight), mLeftPaddle(30, 130), mRightPaddle(450, 130), mBall()
	{
		mMenu = std::make_shared<MainMenu>(*this);
		mPeripherals = new Peripherals();

		mRenderer.ClearAndDraw(0x00);
	}

	Pong::~Pong()
	{
		delete mPeripherals;
		mRenderer.ClearAndDraw(0x00);
	}

	void Pong::Run()
	{	
		while (mRunning)
		{
			OnUpdate();
			OnRender();
		}
	}

	void Pong::OnUpdate()
	{
		mPeripherals->Update();
		mMenu->OnUpdate(mPeripherals);

		if (mState == GameState::Menu)
			return;

		if (mState == GameState::WaitingToStart)
		{
			if (mPeripherals->IsKnobPressed(Peripherals::Knob::Green))
			{
				mBall.Launch();
				mState = GameState::Playing;
			}
		}

		const uint32_t speed = 32;

		mLeftPaddle.Y += mPeripherals->GetKnobDelta(Peripherals::Knob::Red) /* * speed */;
		mRightPaddle.Y += mPeripherals->GetKnobDelta(Peripherals::Knob::Blue) /* * speed */;

		mLeftPaddle.Y = Clamp(mLeftPaddle.Y, 0, cHeight - mLeftPaddle.GetHeight());
		mRightPaddle.Y = Clamp(mRightPaddle.Y, 0, cHeight - mRightPaddle.GetHeight());

		// int left_paddle_y = (mPeripherals->GetKnobPosition(Peripherals::Knob::Red) * cHeight) / speed;
		// int right_paddle_y = (mPeripherals->GetKnobPosition(Peripherals::Knob::Blue) * cHeight) / speed;

		// Keep the paddles in the arena		
		// mLeftPaddle.Y = sClamp(left_paddle_y, 0, cHeight - mLeftPaddle.GetHeight());
		// mRightPaddle.Y = sClamp(right_paddle_y, 0, cHeight - mRightPaddle.GetHeight());

		if (mBall.Overlaps(mLeftPaddle))
		{
			mBall.BounceOff(mLeftPaddle);
			mPointCounter++;
		}
		else if (mBall.Overlaps(mRightPaddle))
		{
			mBall.BounceOff(mRightPaddle);
			mPointCounter++;
		}

		if (HasModierAnyFlags(Modifier::AcceleratingBall))
		{
			mBall.Accelerate();
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

			mRenderer.DrawPaddle(mLeftPaddle, 0xf800);
			mRenderer.DrawPaddle(mRightPaddle, 0x001f);

			mRenderer.DrawBall(mBall, 0xffffffff);
		}
		else if (mState == GameState::Menu)
		{
			mRenderer.Clear(0x00);
			mMenu->OnRender(mRenderer);
		}
		mRenderer.Draw();
	}

	void Pong::StartGame()
	{
		mLeftScore = 0;
		mRightScore = 0;

		mMenu = std::make_shared<GameUI>(*this);

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

		mPointCounter = 1;
		mBall = Ball((cWidth - 2) / 2, (cHeight - 3)/ 2);
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

        mPeripherals->SetLedLine(value);
    }

}
