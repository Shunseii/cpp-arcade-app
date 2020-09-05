#include "Games/Breakout/Ball.h"

#include "Utils/Utils.h"
#include "Graphics/Screen.h"
#include "Shapes/Circle.h"
#include "Games/Breakout/BoundaryEdge.h"

Ball::Ball(): Ball(Vec2D::ZERO, Ball::RADIUS) {}

Ball::Ball(const Vec2D& pos, float radius): 
	mBBox(pos - Vec2D(radius, radius), radius * 2.0f, radius * 2.0f), 
	mVelocity(Vec2D::ZERO) {}

void Ball::Update(uint32_t dt) {
	mBBox.MoveBy(mVelocity * MillisToSecs(dt));
}

void Ball::Draw(Screen& screen) {
	Circle circ = {mBBox.GetCenterPoint(), GetRadius()};
	screen.Draw(circ, Color::Red(), true, Color::Red());
}

void Ball::MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& pointOnEdge, bool limitToEdge) {
	if (edge.normal == DOWN_DIR) {	
		mBBox.MoveTo(Vec2D(
					mBBox.GetTopLeftPoint().GetX(),
					edge.edge.GetP0().GetY() + mBBox.GetHeight()
				));
	} else if (edge.normal == UP_DIR) {	
		mBBox.MoveTo(Vec2D(
					mBBox.GetTopLeftPoint().GetX(),
					edge.edge.GetP0().GetY() - mBBox.GetHeight()
				));
	} else if (edge.normal == RIGHT_DIR) {
		mBBox.MoveTo(Vec2D(
					edge.edge.GetP0().GetX() + edge.normal.GetX(), 
					mBBox.GetTopLeftPoint().GetY())
				);
	} else if (edge.normal == LEFT_DIR) {	
		mBBox.MoveTo(Vec2D(
					edge.edge.GetP0().GetX() - mBBox.GetWidth(),
					mBBox.GetTopLeftPoint().GetY())
				);
	}

	pointOnEdge = edge.edge.ClosestPoint(mBBox.GetCenterPoint(), limitToEdge);
}

void Ball::MoveTo(const Vec2D point) {
	mBBox.MoveTo(point - Vec2D(GetRadius(), GetRadius()));
}
