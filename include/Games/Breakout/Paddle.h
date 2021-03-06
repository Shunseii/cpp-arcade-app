#ifndef BREAKOUT_PADDLE_H_
#define BREAKOUT_PADDLE_H_

#include <stdint.h>
#include "Games/Breakout/Excluder.h"

class Screen;
class Ball;

enum PaddleDirection {
	LEFT = 1 << 0,
	RIGHT = 1 << 1
};

class Paddle : public Excluder {
	private:
		static constexpr float VELOCITY = 100.0f;
		static constexpr float CORNER_BOUNCE_AMNT = 2.0f;

		uint32_t mDirection;
		AARectangle mBoundary; 

	public:
		static const uint32_t PADDLE_WIDTH = 50;
		static const uint32_t PADDLE_HEIGHT = 10;

		void Init(const AARectangle& rect, const AARectangle& boundary);
		void Update(uint32_t dt, Ball& ball);
		void Draw(Screen&);
		bool Bounce(Ball&);

		inline bool IsMovingLeft() const {return mDirection == PaddleDirection::LEFT;}
		inline bool IsMovingRight() const {return mDirection == PaddleDirection::RIGHT;}

		inline void SetMovementDirection(PaddleDirection dir) {mDirection |= dir;}
		inline void UnsetMovementDirection(PaddleDirection dir) {mDirection &= ~dir;}
		inline void StopMovement() {mDirection = 0;}
};

#endif /* BREAKOUT_PADDLE_H_ */
