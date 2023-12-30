#pragma once

#include "utilities.h"
#include "Vector2.h"
#include "Plane.h"

class Collision {

	private:

		// Returns std::pair<float, float>, where first is min value on some created axis, and second being max value
		static std::pair<float, float> FindMinMax(const Vector2& axis, const Plane& plane);

	public:
	
		// Polygon-to-Polygon Collision
		static bool PolygonToPolygon(const Plane& plane_a, const Plane& plane_b);

		// Circle-to-Circle Collision
		static bool CircleToCircle(const Plane& plane_a, const Plane& plane_b);

		// Circle-to-Polygon Collision
		static bool CircleToPolygon(const Plane& plane_a, const Plane& plane_b);
	
};