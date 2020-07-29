#ifndef SHAPES_SHAPE_H
#define SHAPES_SHAPE_H

#include <vector>
#include "Utils/Vec2D.h"

class Shape {
	protected:
		std::vector<Vec2D> mPoints;

	public:
		virtual Vec2D GetCenterPoint() const = 0;
		virtual ~Shape() {}
		inline virtual std::vector<Vec2D> GetPoints() const {return mPoints;}
		void MoveBy(const Vec2D& deltaOffset);
};

#endif
