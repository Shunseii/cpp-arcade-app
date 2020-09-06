#ifndef BREAKOUT_LEVELBOUNDARY_H_
#define BREAKOUT_LEVELBOUNDARY_H_

#include "Games/Breakout/Excluder.h"

class AARectangle;
class Ball;

class LevelBoundary {
	private:
		Excluder mIncluder;
		
		bool HasCollidedWithEdge(const Ball&, const BoundaryEdge&);

	public:
		LevelBoundary() {}
		LevelBoundary(const AARectangle& boundary);

		bool HasCollided(const Ball&, BoundaryEdge&);
		inline const AARectangle& GetAARectangle() {return mIncluder.GetAARectangle();}
};

#endif /* BREAKOUT_LEVELBOUNDARY_H_ */
