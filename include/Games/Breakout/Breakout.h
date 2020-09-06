#ifndef GAMES_BREAKOUT_H_
#define GAMES_BREAKOUT_H_

#include <vector>

#include "Games/Game.h"
#include "Games/Breakout/Paddle.h"
#include "Games/Breakout/Ball.h"
#include "Games/Breakout/LevelBoundary.h"
#include "Games/Breakout/BreakoutGameLevel.h"

enum BreakoutGameState {
	IN_PLAY = 0,
	IN_SERVE,
	IN_GAME_OVER
};

class Breakout : public Game {
	private:
		const float INITIAL_BALL_SPEED = 100;
		const Vec2D INITIAL_BALL_VELOCITY = Vec2D(100, -100);

		Paddle mPaddle;
		Ball mBall;
		LevelBoundary mLevelBoundary;
		std::vector<BreakoutGameLevel> mLevels;
		size_t mCurrentLevel;
		BreakoutGameState mGameState;

		void ResetGame();
		inline BreakoutGameLevel& GetCurrentLevel() {return mLevels[mCurrentLevel];}
		void SetToServeState();

	public:
		virtual void Init(GameController&) override;
		virtual void Update(uint32_t dt) override;
		virtual void Draw(Screen&) override;
		virtual const std::string& GetName() const override;
};

#endif /* GAMES_BREAKOUT_H_ */
