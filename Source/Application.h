#pragma once

#include "Peripherals.h"
#include "Renderer.h"
#include "Paddle.h"
#include "Ball.h"

#include "Menu/Menu.h"

namespace Pong {

	/// Enum that determines which modifiers are enabled
	enum class Modifier : uint32_t
    {
        None = 0,
        AcceleratingBall = 0x1,      ///< Ball increases it's speed after it bounces off of a paddle
        AdditivePointSystem = 0x2,   ///< Number of points when a player scores is equal to the number of bounces during the last exchange
        Attrition = 0x4,             ///< Paddles wear off after each bounce
    };

	// Overloads for bitwise operators
    inline Modifier operator &= (Modifier& inLHS, Modifier inRHS) { return inLHS = (Modifier)((uint32_t)inLHS & (uint32_t)inRHS); }
    inline Modifier operator |= (Modifier& inLHS, Modifier inRHS) { return inLHS = (Modifier)((uint32_t)inLHS | (uint32_t)inRHS); }
    inline Modifier operator ~ (Modifier inLHS) { return (Modifier)~(uint32_t)inLHS; }

	/// Enum for identifying the current application's state
	enum class GameState
	{
		Menu,
		WaitingToStart,
		Playing,
	};

	struct ModifierState;

	/// Contains the entire application
	class Application
	{
	public:
		/// Constructor
		Application();

		/// Destructor
		~Application();

		/// The main loop
		void Run();

		/// Update the application
		void OnUpdate();

		/// Render the application to the LCD display
		void OnRender();

		/// Start a brand new game
		void StartGame();

		/// Return from Playing state back to Menu state
		void ReturnToMainMenu();

		void SetModifier(ModifierState inModifier);

		template<typename T>
		void SetMenu() { mMenu = std::make_shared<T>(*this); }

		/// Close the application
		void Close() { mRunning = false; }

		/// Getters
		uint32_t GetLeftScore() const { return mLeftScore; }
		uint32_t GetRightScore() const { return mRightScore; }
		Modifier GetModifier() const { return mModifier; }
	
		static constexpr uint32_t cWidth = 480;				///< Width of the board's LCD display
		static constexpr uint32_t cHeight = 320;			///< Height of the board's LCD display

	private:
		// Reset the board so that the ball can be launched
		void ResetBoard();

		void UpdateLedLine();

		// Helper function to see if a certain modifier is enabled
		inline bool HasModierAnyFlags(Modifier inContains) const { return (uint32_t(mModifier) & uint32_t(inContains)) != 0; }

		Renderer mRenderer;

		Paddle mLeftPaddle;
		Paddle mRightPaddle;
		Ball mBall;

		Peripherals* mPeripherals;
		std::shared_ptr<Menu> mMenu;

		GameState mState = GameState::Menu;

		uint32_t mLeftScore = 0;							///< Score of the left (red) player
		uint32_t mRightScore = 0;							///< Score of the right (blue) player

		uint32_t mPointCounter = 0;							///< Used only when AdditivePointSystem is enabled

		Modifier mModifier = Modifier::None;
		uint32_t mRGBLedColor = 0x0;						///< Color of the RGB LED's

		bool mLeftWonLastGame = false;

		bool mRunning = true;
	};

}
