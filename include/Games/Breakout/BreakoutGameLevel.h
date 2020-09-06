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
		static const int BLOCK_WIDTH = 16;
		static const int BLOCK_HEIGHT = 28;
		
		std::vector<Block> mBlocks;

		void CreateDefaultLevel(const AARectangle& boundary);

	public:
		BreakoutGameLevel();

		void Init(const AARectangle& boundary);
		void Load(const std::vector<Block>& blocks);
		void Update(uint32_t dt, Ball& ball);
		void Draw(Screen&);

		static std::vector<BreakoutGameLevel> LoadLevelsFromFile(const std::string& filePath);
};

#endif /* BREAKOUT_BREAKOUTGAMELEVEL_H_ */
