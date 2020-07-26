#ifndef __VEC2D_H__
#define __VEC2D_H__

#include <iostream>

class Vec2D {
	private:
		float mX;
		float mY;

	public:
		static const Vec2D ZERO;
		
		Vec2D();
		Vec2D(float, float);

		inline void SetX(float x) {this->mX = x;}	
		inline void SetY(float y) {this->mY = y;}
		inline float GetX() const {return this->mX;}	
		inline float GetY() const {return this->mY;}

		friend std::ostream& operator<<(std::ostream&, const Vec2D&);
		
		bool operator==(const Vec2D&) const;
		bool operator!=(const Vec2D&) const;

		Vec2D operator-() const;
		Vec2D operator*(float) const;
		Vec2D operator/(float) const;
		Vec2D& operator*=(float);
		Vec2D& operator/=(float);

		Vec2D operator+(const Vec2D&) const;
		Vec2D operator-(const Vec2D&) const;
		Vec2D& operator+=(const Vec2D&);
		Vec2D& operator-=(const Vec2D&);
	
		float Mag() const;
		float Mag2() const;
		
		Vec2D GetUnitVec() const;
		Vec2D& Normalize();
		
		float Distance(const Vec2D&) const;	
		float Dot(const Vec2D&) const;
		
		float AngleBetween(const Vec2D&) const;
		Vec2D ProjectOnto(const Vec2D&) const;
		Vec2D Reflect(const Vec2D&) const;
		
		void Rotate(float, const Vec2D&);
		Vec2D RotationResult(float, const Vec2D&) const;

		friend Vec2D operator*(float, const Vec2D&);
};

#endif
