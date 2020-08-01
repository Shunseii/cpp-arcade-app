#include "Shapes/Circle.h"

#include "Utils/Utils.h"

Circle::Circle(): Circle(Vec2D::ZERO, 0) {}

Circle::Circle(const Vec2D& center, float radius): mRadius(radius) {
	mPoints.push_back(center);
}

bool Circle::Intersects(const Circle& circle) const {
	return GetCenterPoint().Distance(circle.GetCenterPoint()) 
		< (mRadius + circle.mRadius);
}

bool Circle::ContainsPoint(const Vec2D& point) const {
	return IsLessThanOrEqual(GetCenterPoint().Distance(point), mRadius);
}
