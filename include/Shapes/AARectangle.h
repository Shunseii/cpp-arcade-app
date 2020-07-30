#ifndef SHAPES_AARECTANGLE_H
#define SHAPES_AARECTANGLE_H

#include "Shapes/Shape.h"

// Axis-aligned Rectangle
class AARectangle: public Shape {
	public:
		AARectangle();
		AARectangle(const Vec2D& topLeft, unsigned int width, unsigned int height);
		AARectangle(const Vec2D& topLeft, const Vec2D& bottomRight);
		
		inline void SetTopLeftPoint(const Vec2D& topLeft) {mPoints[0] = topLeft;}
		inline void SetBottomRightPoint(const Vec2D& bottomRight) {mPoints[1] = bottomRight;}

		inline Vec2D GetTopLeftPoint() const {return mPoints[0];}
		inline Vec2D GetBottomRightPoint() const {return mPoints[1];}

		float GetWidth() const;
		float GetHeight() const;

		void MoveTo(const Vec2D& pos);

		virtual Vec2D GetCenterPoint() const override;

		bool Intersects(const AARectangle&) const;
		bool ContainsPoint(const Vec2D&) const;

		static AARectangle Inset(const AARectangle&, Vec2D& insets);

		virtual std::vector<Vec2D> GetPoints() const override;
};

#endif
