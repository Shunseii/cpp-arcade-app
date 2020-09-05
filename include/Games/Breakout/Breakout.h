#ifndef GAMES_BREAKOUT_H_
#define GAMES_BREAKOUT_H_

#include "Games/Game.h"
#include "Games/Breakout/Paddle.h"

class Breakout : public Game {
	private:
		Paddle mPaddle;

		void ResetGame();

	public:
		virtual void Init(GameController&) override;
		virtual void Update(uint32_t dt) override;
		virtual void Draw(Screen&) override;
		virtual const std::string& GetName() const override;
};

#endif /* GAMES_BREAKOUT_H_ */
