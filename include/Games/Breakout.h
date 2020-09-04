#ifndef GAMES_BREAKOUT_H_
#define GAMES_BREAKOUT_H_

#include "Game.h"

class Breakout : public Game {
	public:
		virtual void Init(GameController&) override;
		virtual void Update(uint32_t dt) override;
		virtual void Draw(Screen&) override;
		virtual std::string GetName() const override;
};

#endif /* GAMES_BREAKOUT_H_ */
