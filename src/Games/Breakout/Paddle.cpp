#include "Games/Breakout/Paddle.h"

#include "Graphics/Screen.h"
#include "Graphics/Color.h"
#include "Utils/Utils.h"
#include "Games/Breakout/BoundaryEdge.h"

void Paddle::Init(const AARectangle& rect, const AARectangle& boundary) {
	Excluder::Init(rect);
	mBoundary = boundary;
	mDirection = 0;
}

void Paddle::Update(uint32_t dt) {
	if (mDirection != 0) {
		Vec2D dir;
		
		if ((mDirection & PaddleDirection::LEFT) == PaddleDirection::LEFT &&
				(mDirection & PaddleDirection::RIGHT) == PaddleDirection::RIGHT) {
			dir = Vec2D::ZERO;
		} else if (mDirection == PaddleDirection::LEFT) {
			dir = LEFT_DIR;
		} else {
			dir = RIGHT_DIR;
		}

		Vec2D dx = dir * VELOCITY * MillisToSecs(dt);

		MoveBy(dx);

		const AARectangle& rect = GetAARectangle();

		if (IsGreaterThanOrEqual(
					mBoundary.GetTopLeftPoint().GetX(), 
					rect.GetTopLeftPoint().GetX())
				) {
			MoveTo(Vec2D(
						mBoundary.GetTopLeftPoint().GetX(), 
						rect.GetTopLeftPoint().GetY())
					);
		} else if (IsGreaterThanOrEqual(
					rect.GetBottomRightPoint().GetX(), 
					mBoundary.GetBottomRightPoint().GetX())
				) {
			MoveTo(Vec2D(mBoundary.GetBottomRightPoint().GetX() - rect.GetWidth(), 
						rect.GetTopLeftPoint().GetY()));
		}
	}
}

void Paddle::Draw(Screen& screen) {
	screen.Draw(GetAARectangle(), Color::Blue(), true, Color::Blue());
}
