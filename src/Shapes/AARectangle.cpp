#include "Shapes/AARectangle.h"

#include <cmath>
#include "Utils/Vec2D.h"
#include "Utils/Utils.h"

AARectangle::AARectangle(): AARectangle(Vec2D::ZERO, Vec2D::ZERO) {}

AARectangle::AARectangle(const Vec2D& topLeft, unsigned int width, unsigned int height): 
	AARectangle(topLeft, Vec2D(topLeft.GetX() + width - 1, topLeft.GetY() + height - 1)) {}

AARectangle::AARectangle(const Vec2D& topLeft, const Vec2D& bottomRight) {
	mPoints.push_back(topLeft);
	mPoints.push_back(bottomRight);
}

float AARectangle::GetWidth() const {
	return GetBottomRightPoint().GetX() - GetTopLeftPoint().GetX() + 1;
}

float AARectangle::GetHeight() const {	
	return GetTopLeftPoint().GetY() - GetBottomRightPoint().GetY() + 1;
}

void AARectangle::MoveTo(const Vec2D& pos) {
	float width = GetWidth();
	float height = GetHeight();

	SetTopLeftPoint(pos);
	SetBottomRightPoint(Vec2D(pos.GetX() + width - 1, pos.GetY() + height - 1));
}

Vec2D AARectangle::GetCenterPoint() const {
	return Vec2D(GetTopLeftPoint().GetX() + GetWidth() / 2.0f, 
			GetTopLeftPoint().GetY() + GetHeight() / 2.0f);
}

bool AARectangle::Intersects(const AARectangle& otherRect) const {
	return !(otherRect.GetBottomRightPoint().GetX() < GetTopLeftPoint().GetX() || 
			otherRect.GetTopLeftPoint().GetX() > GetBottomRightPoint().GetX() || 
			otherRect.GetBottomRightPoint().GetY() > GetTopLeftPoint().GetY() ||
			otherRect.GetTopLeftPoint().GetY() < GetBottomRightPoint().GetY());
}

bool AARectangle::ContainsPoint(const Vec2D& point) const {
	bool withinX = point.GetX() >= GetTopLeftPoint().GetX() 
		&& point.GetX() <= GetBottomRightPoint().GetX();
	bool withinY = point.GetY() >= GetBottomRightPoint().GetY() 
		&& point.GetY() <= GetTopLeftPoint().GetY();
	
	return withinX && withinY;
}

AARectangle AARectangle::Inset(const AARectangle& rect, Vec2D& insets) {
	return AARectangle(rect.GetTopLeftPoint() + insets, 
			rect.GetWidth() - 2 * insets.GetX(), 
			rect.GetHeight() - 2 * insets.GetY());
}

std::vector<Vec2D> AARectangle::GetPoints() const {
	std::vector<Vec2D> points;

	points.push_back(mPoints[0]); // top left
	points.push_back(Vec2D(mPoints[1].GetX(), mPoints[0].GetY())); // top right
	points.push_back(mPoints[1]); // bottom right
	points.push_back(Vec2D(mPoints[0].GetX(), mPoints[1].GetY())); // bottom left

	return points;
}
