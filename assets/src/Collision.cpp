#include "Collision.h"

// Polygon-to-Polygon Collision
bool Collision::PolygonToPolygon(const Plane& plane_a, const Plane& plane_b) {

	/* GOAL:
	* Get orthogonal vector to some edge
	* Project vertices onto orthogonal vector
	* Get min and max vertices on orthogonal vector
	* Check if there is a gap between segments of plane a and plane b
	* Repeat for all edges and planes
	*/

	std::vector<Plane> planes{ plane_a, plane_b };

	// std::vector for less repetition of checking both plane_a and plane_b
	for (Plane plane : planes) {

		for (size_t j{ 1 }; j < plane.GetVertices().size(); ++j) {

			// Initialize x_0, y_0, x, and y values to make a displacement vector of one side
			float init_x{ plane.GetVertices().at(j).position.x };
			float init_y{ plane.GetVertices().at(j).position.y };
			
			float terminal_x{ plane.GetVertices().at((j == static_cast<size_t>(plane.GetVertices().size() - 1)) ?
													 (((j + 1) % plane.GetVertices().size()) + 1) :
													 ((j + 1) % plane.GetVertices().size())).position.x };
			float terminal_y{ plane.GetVertices().at((j == static_cast<size_t>(plane.GetVertices().size() - 1)) ?
													 (((j + 1) % plane.GetVertices().size()) + 1) :
													 ((j + 1) % plane.GetVertices().size())).position.y };

			// Get normal to displacement vector serving as axis
			Vector2 axis(Vector2::UnitVector(Vector2::GetOrthogonal(Vector2(init_x, init_y, terminal_x, terminal_y))));

			// Find min and max values of both plane_a and plane_b on axis
			std::pair<float, float> plane_a_min_max{ FindMinMax(axis, plane_a) };
			float min_a{ plane_a_min_max.first };
			float max_a{ plane_a_min_max.second };

			std::pair<float, float> plane_b_min_max{ FindMinMax(axis, plane_b) };
			float min_b{ plane_b_min_max.first };
			float max_b{ plane_b_min_max.second };

			// Return true if no overlap between min and max values of plane_a and plane_b (no collision)
			if ((min_a < min_b && max_a <= min_b) ||
				(min_b < min_a && max_b <= min_a)) {
				return true;
			}

		}

	}

	return false;

}

// Circle-to-Circle Collision
bool Collision::CircleToCircle(const Plane& plane_a, const Plane& plane_b) {

	return false;

}

// Circle-to-Polygon Collision
bool Collision::CircleToPolygon(const Plane& plane_a, const Plane& plane_b) {

	return false;

}

std::pair<float, float> Collision::FindMinMax(const Vector2& axis, const Plane& plane) {

	float min{ INFINITY };
	float max{ -INFINITY };

	for (size_t i{ 1 }; i < plane.GetVertices().size(); ++i) {

		float projection{ Vector2::Dot(Vector2(std::make_pair(plane.GetVertices().at(i).position.x, plane.GetVertices().at(i).position.y)), axis) };

		if (projection > max) { max = projection; }

		if (projection < min) { min = projection; }

	}

	return std::make_pair(min, max);

}
