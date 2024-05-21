#pragma once

#include "Peripherals.h"
#include "Renderer.h"
#include "Paddle.h"
#include "Ball.h"

#include "Menu/Menu.h"

namespace Pong {

	enum class Modifier : uint32_t
    {
        None = 0,
        AcceleratingBall = 0x1,      // Ball increases it's speed after it bounces off of a paddle
        AdditivePointSystem = 0x2,   // Number of points when a player scores is equal to the number of bounces during the last exchange
        Attrition = 0x4,             // Paddles wear off after each bounce
    };

    inline Modifier operator &= (Modifier& inLHS, Modifier inRHS) { return inLHS = (Modifier)((uint32_t)inLHS & (uint32_t)inRHS); }
    inline Modifier operator |= (Modifier& inLHS, Modifier inRHS) { return inLHS = (Modifier)((uint32_t)inLHS | (uint32_t)inRHS); }
    inline Modifier operator ~ (Modifier inLHS) { return (Modifier)~(uint32_t)inLHS; }

	enum class GameState
	{
		Menu,
		WaitingToStart,
		Playing,
	};

	class Pong
	{
	public:
		Pong();
		~Pong();

		void Run();
		void OnUpdate();
		void OnRender();

		void StartGame();
		void ReturnToMainMenu();

		void SetModifier(ModifiersMenu::ModifierState inModifier);

		template<typename T>
		void SetMenu() { mMenu = std::make_shared<T>(*this); }

		void Close() { mRunning = false; }

		uint32_t GetLeftScore() const { return mLeftScore; }
		uint32_t GetRightScore() const { return mRightScore; }
		Modifier GetModifier() const { return mModifier; }
	
		static constexpr uint32_t cWidth = 480;
		static constexpr uint32_t cHeight = 320;

	private:
		void ResetBoard();
		void UpdateLedLine();

		inline bool HasModierAnyFlags(Modifier inContains) const { return (uint32_t(mModifier) & uint32_t(inContains)) != 0; }

		Renderer mRenderer;

		Paddle mLeftPaddle;
		Paddle mRightPaddle;
		Ball mBall;

		Peripherals* mPeripherals;
		std::shared_ptr<Menu> mMenu;

		GameState mState = GameState::Menu;

		uint32_t mLeftScore = 0;
		uint32_t mRightScore = 0;

		uint32_t mPointCounter = 0; // Used only when AdditivePointSystem is enabled

		Modifier mModifier = Modifier::None;
		uint32_t mRGBLedColor = 0x0;

		bool mRunning = true;
	};

}
