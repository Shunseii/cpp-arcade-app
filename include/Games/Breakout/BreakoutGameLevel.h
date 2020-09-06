#ifndef BREAKOUT_BREAKOUTGAMELEVEL_H_
#define BREAKOUT_BREAKOUTGAMELEVEL_H_

#include <vector>
#include <stdint.h>
#include "Games/Breakout/Block.h"

class Screen;
class Ball;
class AARectangle;

class BreakoutGameLevel {
	private:
		std::vector<Block> mBlocks;

		void CreateDefaultLevel(const AARectangle& boundary);

	public:
		BreakoutGameLevel();

		void Init(const AARectangle& boundary);
		void Load(const std::vector<Block>& blocks);
		void Update(uint32_t dt, Ball& ball);
		void Draw(Screen&);

};

#endif /* BREAKOUT_BREAKOUTGAMELEVEL_H_ */
