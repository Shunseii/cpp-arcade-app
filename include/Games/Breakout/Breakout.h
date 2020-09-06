#ifndef GAMES_BREAKOUT_H_
#define GAMES_BREAKOUT_H_

#include "Games/Game.h"
#include "Games/Breakout/Paddle.h"
#include "Games/Breakout/Ball.h"
#include "Games/Breakout/LevelBoundary.h"
#include "Games/Breakout/BreakoutGameLevel.h"

class Breakout : public Game {
	private:
		const Vec2D INITIAL_BALL_VELOCITY = Vec2D(100, -100);

		Paddle mPaddle;
		Ball mBall;
		LevelBoundary mLevelBoundary;
		BreakoutGameLevel mLevel;

		void ResetGame();

	public:
		virtual void Init(GameController&) override;
		virtual void Update(uint32_t dt) override;
		virtual void Draw(Screen&) override;
		virtual const std::string& GetName() const override;
};

#endif /* GAMES_BREAKOUT_H_ */
