#ifndef BREAKOUT_BALL_H_
#define BREAKOUT_BALL_H_

#include <stdint.h>
#include "Shapes/AARectangle.h"

class Screen;
struct BoundaryEdge;

class Ball {
	private:
		AARectangle mBBox;
		Vec2D mVelocity;

		static constexpr float RADIUS = 5.0f;

	public:
		Ball();
		Ball(const Vec2D& pos, float radius);

		void Update(uint32_t dt);
		void Draw(Screen&);
		void MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& pointOnEdge, bool limitToEdge);
		
		void MoveTo(const Vec2D point);
		void Bounce(const BoundaryEdge& edge);

		inline void Stop() {mVelocity = Vec2D::ZERO;}
		inline const AARectangle GetBoundingBox() const {return mBBox;}

		inline void SetVelocity(const Vec2D& velocity) {mVelocity = velocity;}
		inline Vec2D GetVelocity() {return mVelocity;}
		inline float GetRadius() const {return mBBox.GetWidth() / 2.0f;}
		inline Vec2D GetPosition() const {return mBBox.GetCenterPoint();}
};

#endif /* BREAKOUT_BALL_H_ */
