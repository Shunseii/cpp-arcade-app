#ifndef SHAPES_CIRCLE_H
#define SHAPES_CIRCLE_H

#include "Shapes/Shape.h"

class Circle: public Shape {
	private:
		float mRadius;
	
	public:
		Circle();
		Circle(const Vec2D& center, float radius);

		inline virtual Vec2D GetCenterPoint() const override {return mPoints[0];}
		inline float GetRadius() const {return mRadius;}
		inline void SetRadius(float radius) {mRadius = radius;}
		inline void MoveTo(const Vec2D& pos) {mPoints[0] = pos;}

		bool Intersects(const Circle&) const;
		bool ContainsPoint(const Vec2D& point) const;
};

#endif
