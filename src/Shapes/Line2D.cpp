#include "Shapes/Line2D.h"

#include <cmath>
#include "Utils/Vec2D.h"
#include "Utils/Utils.h"

Line2D::Line2D(): Line2D(Vec2D::ZERO, Vec2D::ZERO) {}

Line2D::Line2D(float x0, float y0, float x1, float y1): 
	Line2D(Vec2D(x0, y0), Vec2D(x1, y1)) {}

Line2D::Line2D(const Vec2D p0, const Vec2D p1): mP0(p0), mP1(p1) {}

bool Line2D::operator==(const Line2D& line) const {
	return mP0 == line.GetP0() && mP1 == line.GetP1();
}

Vec2D Line2D::Midpoint() const {
	return Vec2D((mP1.GetX() + mP0.GetX()) / 2.0f, 
			(mP1.GetY() + mP0.GetY()) / 2.0f);
}

float Line2D::Slope() {
	float dx = mP1.GetX() - mP0.GetX();

	if (fabsf(dx) < EPSILON) {
		return 0;
	}

	return mP1.GetY() - mP0.GetY() / dx;
}

float Line2D::Length() {
	return mP1.Distance(mP0);
}

float Line2D::MinDistanceFrom(const Vec2D& p, bool limitToSegment) const {
	return p.Distance(ClosestPoint(p, limitToSegment));
}

Vec2D Line2D::ClosestPoint(const Vec2D p, bool limitToSegment) const {
	Vec2D p0ToP = p - mP0;
	Vec2D p0ToP1 = mP1 - mP0;

	float l2 = p0ToP1.Mag2();

	float dot = p0ToP.Dot(p0ToP1);
	float t = dot / l2;
	
	if (limitToSegment) {
		// Clamp value of t
		t = std::fmax(0, std::fmin(1.0f, t));
	}

	return mP0 + p0ToP1 * t;
}
