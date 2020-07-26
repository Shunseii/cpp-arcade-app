#ifndef SHAPES_LINE2D_H
#define SHAPES_LINE2D_H

#include "Utils/Vec2D.h"

class Line2D {
	private:
		Vec2D mP0, mP1;

	public:
		Line2D();
		Line2D(float x0, float y0, float x1, float y1);
		Line2D(const Vec2D p0, const Vec2D p1);

		inline const Vec2D& GetP0() const {return mP0;}
		inline const Vec2D& GetP1() const {return mP1;}
		inline void SetP0(const Vec2D& p0) {mP0 = p0;}
		inline void SetP1(const Vec2D& p1) {mP1 = p1;}

		bool operator==(const Line2D&) const;
		float MinDistanceFrom(const Vec2D& p, bool limitToSegment = false) const;
		Vec2D ClosestPoint(const Vec2D p, bool limitToSegment = false) const;
		
		Vec2D Midpoint() const;
		float Slope();
		float Length();
};

#endif
