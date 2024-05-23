#include "Application.h"
#include "Peripherals.h"
#include "Utils.h"

#include "Menu/GameUI.h"
#include "Menu/MainMenu.h"
#include "Menu/ModifiersMenu.h"

#include <iostream>

namespace Pong {

	Application::Application()
		: mRenderer(cWidth, cHeight), mLeftPaddle(30, 130), mRightPaddle(450, 130), mBall()
	{
		mMenu = std::make_shared<MainMenu>(*this);
		mPeripherals = new Peripherals();
		mPeripherals->SetRGBLEDs(mRGBLedColor);
	}

	Application::~Application()
	{
		mPeripherals->SetRGBLEDs(0x0);
		delete mPeripherals;

		mRenderer.ClearAndDraw(0x0);

		mPointCounter = 0;
		mLeftScore = 0;
		mRightScore = 0;
		UpdateLedLine();
	}

	void Application::Run()
	{	
		while (mRunning)
		{
			OnUpdate();
			OnRender();
		}
	}

	void Application::OnUpdate()
	{
		mPeripherals->Update();
		mPeripherals->SetRGBLEDs(mRGBLedColor);
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

		if (HasModierAnyFlags(Modifier::AdditivePointSystem))
		{
			if (mLeftScore >= 50 || mRightScore >= 50)
				ReturnToMainMenu();
		}
		else
		{
			if (mLeftScore == 16 || mRightScore == 16)
				ReturnToMainMenu();
		}

		const uint32_t speed = 8;

		mLeftPaddle.Y += mPeripherals->GetKnobDelta(Peripherals::Knob::Red) * speed;
		mRightPaddle.Y += mPeripherals->GetKnobDelta(Peripherals::Knob::Blue) * speed;

		mLeftPaddle.Y = Clamp(mLeftPaddle.Y, 0, cHeight - mLeftPaddle.GetHeight());
		mRightPaddle.Y = Clamp(mRightPaddle.Y, 0, cHeight - mRightPaddle.GetHeight());

		bool attrition = HasModierAnyFlags(Modifier::Attrition);

		if (mBall.Overlaps(mLeftPaddle, attrition))
		{
			mBall.BounceOff(mLeftPaddle);
			mPointCounter++;

			if (HasModierAnyFlags(Modifier::AcceleratingBall))
			mBall.Accelerate();
		}
		else if (mBall.Overlaps(mRightPaddle, attrition))
		{
			mBall.BounceOff(mRightPaddle);
			mPointCounter++;

			if (HasModierAnyFlags(Modifier::AcceleratingBall))
			mBall.Accelerate();
		}

		mBall.OnUpdate();

		// Check if the ball has gone out of screen
		if (mBall.GetX() < 0)
		{
			if (HasModierAnyFlags(Modifier::AdditivePointSystem))
				mRightScore += mPointCounter;
			else
				mRightScore++;

			mLeftWonLastGame = false;
			ResetBoard();
		}
		else if (mBall.GetX() + Ball::cSize > cWidth)
		{
			if (HasModierAnyFlags(Modifier::AdditivePointSystem))
				mLeftScore += mPointCounter;
			else
				mLeftScore++;

			mLeftWonLastGame = true;
			ResetBoard();
		}

		UpdateLedLine();
	}

	void Application::OnRender()
	{
		if (mState == GameState::Playing || mState == GameState::WaitingToStart)
		{
			mRenderer.Clear();
			mMenu->OnRender(mRenderer);

			bool attrition = HasModierAnyFlags(Modifier::Attrition);
			mRenderer.DrawPaddle(mLeftPaddle, attrition, 0xf800);
			mRenderer.DrawPaddle(mRightPaddle, attrition, 0x001f);

			mRenderer.DrawBall(mBall, 0xffff);
		}
		else if (mState == GameState::Menu)
		{
			mRenderer.Clear();
			mMenu->OnRender(mRenderer);
		}
		mRenderer.Draw();
	}

	void Application::StartGame()
	{
		SetMenu<GameUI>();

		mLeftScore = 0;
		mRightScore = 0;

		mLeftPaddle.Reset();
		mRightPaddle.Reset();
		ResetBoard();
	}

	void Application::ReturnToMainMenu()
	{
		SetMenu<MainMenu>();
		mState = GameState::Menu;

		mPointCounter = 0;
		mLeftScore = 0;
		mRightScore = 0;
		UpdateLedLine();
	}

	void Application::SetModifier(ModifierState inModifier)
	{
		if (inModifier.Enabled)
		{
			mModifier |= inModifier.Mod;
			mRGBLedColor += inModifier.Color;
		}
		else
		{
			mModifier &= ~inModifier.Mod;
			mRGBLedColor -= inModifier.Color;
		}
	}

	void Application::ResetBoard()
	{
		UpdateLedLine();

		mPointCounter = 1;
		mBall = Ball((cWidth - 2) / 2, (cHeight - 3)/ 2);
		mState = GameState::WaitingToStart;

		if (mLeftWonLastGame)
			mRightPaddle.Reset();
		else
			mLeftPaddle.Reset();
	}

	void Application::UpdateLedLine()
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

        mPeripherals->SetLEDLine(value);
    }

}
