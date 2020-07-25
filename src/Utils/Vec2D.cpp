#include <iostream>
#include <cassert>
#include <cmath>

#include "Utils/Vec2D.h"
#include "Utils/Utils.h"

const Vec2D Vec2D::ZERO{};

Vec2D::Vec2D(): Vec2D(0, 0) {}

Vec2D::Vec2D(float x, float y): mX{x}, mY{y} {}

std::ostream& operator<<(std::ostream& out, const Vec2D& vec2) {
	std::cout << "X: " << vec2.mX << ", Y: " << vec2.mY << std::endl;
	return out;
}

bool Vec2D::operator==(const Vec2D& vec2) const {
	return IsEqual(mX, vec2.mX) && IsEqual(mY, vec2.mY);
}

bool Vec2D::operator!=(const Vec2D& vec2) const {
	return !(*this == vec2);
}

Vec2D Vec2D::operator-() const {
	return Vec2D(-mX, -mY);
}

Vec2D Vec2D::operator*(float scalar) const {
	return Vec2D(mX * scalar, mY * scalar);
}

Vec2D Vec2D::operator/(float scalar) const {
	assert(fabsf(scalar) > EPSILON);

	return Vec2D(mX / scalar, mY / scalar);
}

Vec2D& Vec2D::operator*=(float scalar) {
	*this = *this * scalar;

	return *this;
}

Vec2D& Vec2D::operator/=(float scalar) {
	*this = *this / scalar;

	return *this;
}

Vec2D Vec2D::operator+(const Vec2D& vec2) const {
	return Vec2D(mX + vec2.mX, mY + vec2.mY);
}

Vec2D Vec2D::operator-(const Vec2D& vec2) const {
	return Vec2D(mX - vec2.mX, mY - vec2.mY);
}

Vec2D& Vec2D::operator+=(const Vec2D& vec2) {
	*this = *this + vec2;

	return *this;
}

Vec2D& Vec2D::operator-=(const Vec2D& vec2) {
	*this = *this - vec2;

	return *this;
}

float Vec2D::Mag() const {
	return sqrt(Mag2());
}

float Vec2D::Mag2() const {
	return Dot(*this);
}

Vec2D Vec2D::GetUnitVec() const {
	float mag = Mag();

	if (mag > EPSILON) {
		return *this / mag;
	}

	return Vec2D::ZERO;
}

Vec2D& Vec2D::Normalize() {
	float mag = Mag();

	if (mag > EPSILON) {
		*this = *this / mag;
	}

	return *this;
}

float Vec2D::Distance(const Vec2D& vec2) const {
	return (vec2 - *this).Mag();
}

float Vec2D::Dot(const Vec2D& vec2) const {
	return mX * vec2.mX + mY * vec2.mY;
}

float Vec2D::AngleBetween(const Vec2D& vec2) const {
	return acosf(GetUnitVec().Dot(vec2.GetUnitVec()));
}

Vec2D Vec2D::ProjectOnto(const Vec2D& vec2) const {
	Vec2D unitVec = vec2.GetUnitVec();
	float dot = Dot(vec2);	

	return dot * unitVec;
}

Vec2D Vec2D::Reflect(const Vec2D& normal) const {
	return *this - 2 * ProjectOnto(normal);
}

void Vec2D::Rotate(float angle, const Vec2D& aroundPoint) {
	float cosine = cosf(angle);
	float sine = sinf(angle);

	Vec2D thisVec(mX, mY);

	thisVec -= aroundPoint;

	float xRot = thisVec.mX * cosine - thisVec.mY * sine;
	float yRot = thisVec.mX * sine + thisVec.mY * cosine;

	Vec2D rot = Vec2D(xRot, yRot);
	*this = rot + aroundPoint;
}

Vec2D Vec2D::RotationResult(float angle, const Vec2D& aroundPoint) const {
	float cosine = cosf(angle);
	float sine = sinf(angle);

	Vec2D thisVec(mX, mY);

	thisVec -= aroundPoint;

	float xRot = thisVec.mX * cosine - thisVec.mY * sine;
	float yRot = thisVec.mX * sine + thisVec.mY * cosine;

	Vec2D rot = Vec2D(xRot, yRot);
	return rot + aroundPoint;
}

Vec2D operator*(float scalar, const Vec2D& vec2) {
	return vec2 * scalar;
}
