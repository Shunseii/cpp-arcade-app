#ifndef BREAKOUT_EXCLUDER_H_
#define BREAKOUT_EXCLUDER_H_

#include "Shapes/AARectangle.h"
#include "Games/Breakout/BoundaryEdge.h"

class Excluder {
	private:
		AARectangle mRect;
		BoundaryEdge mEdges[NUM_EDGES];
		bool mReverseNormals;

		void SetupEdges();

	public:
		virtual ~Excluder() {}

		void Init(const AARectangle&, bool reverseNormals = false);
		bool HasCollided(const AARectangle&, BoundaryEdge&) const;
		Vec2D GetCollisionOffset(const AARectangle&) const;

		inline AARectangle& GetAARectangle() {return mRect;}

		void MoveBy(const Vec2D& delta);
		void MoveTo(const Vec2D& point);
		const BoundaryEdge& GetEdge(EdgeType edge) const;

};

#endif /* BREAKOUT_EXCLUDER_H_ */
