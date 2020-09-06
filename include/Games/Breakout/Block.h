#ifndef BREAKOUT_BLOCK_H_
#define BREAKOUT_BLOCK_H_

#include "Games/Breakout/Excluder.h"
#include "Graphics/Color.h"

class Ball;
class Screen;
class BoundaryEdge;

class Block: public Excluder {
	private:
		Color mOutlineColor;
		Color mFillColor;

		int mHp;

	public:
		static const int UNBREAKABLE = -1;

		Block();
		void Init(
				const AARectangle&, 
				int hp, 
				const Color& outlineColor, 
				const Color& fillColor);
		void Draw(Screen& screen);
		void Bounce(Ball& ball, const BoundaryEdge& edge);

		void ReduceHP();

		inline bool IsDestroyed() const {return mHp == 0;}
		inline int GetHP() const {return mHp;}
		inline const Color& GetOutlineColor() const {return mOutlineColor;}
		inline const Color& GetFillColor() const {return mFillColor;}

};

#endif /* BREAKOUT_BLOCK_H_ */
