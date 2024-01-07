#include "Collision.h"

// Calls a Collision Function based on the plane type
bool Collision::CheckCollision(const Plane& plane_a, const Plane& plane_b) {

	if (plane_a.IsPolygon() && plane_b.IsPolygon()) {

		return PolygonToPolygon(plane_a, plane_b);

	} else if ((plane_a.IsPolygon() && !plane_b.IsPolygon()) ||
			   (!plane_a.IsPolygon() && plane_b.IsPolygon())) {

		return CircleToPolygon(plane_a, plane_b);

	} else {

		return CircleToCircle(plane_a, plane_b);

	}

}

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

	// Create direction for plane_b to get pushed out of plane_a in case of collision
	Vector2 push_vector = Vector2::UnitVector(Vector2(plane_a.GetXPos(), plane_a.GetYPos(),
													  plane_b.GetXPos(), plane_b.GetYPos()));

	// Holds minimum amount to push pane_b out of plane_a
	float prev_depth{ INFINITY };

	// std::vector for less repetition of checking both plane_a and plane_b
	for (Plane plane : planes) {

		for (size_t j{ 1 }; j < plane.GetVertices().size(); ++j) {

			// Initialize x_0, y_0, x, and y values to make a displacement vector of one side
			float init_x{ plane.GetVertices().at(j).position.x };
			float init_y{ plane.GetVertices().at(j).position.y };
			
			size_t index{ (j == static_cast<size_t>(plane.GetVertices().size() - 1)) ?
						  (((j + 1) % plane.GetVertices().size()) + 1) :
						  ((j + 1) % plane.GetVertices().size()) };

			float terminal_x{ plane.GetVertices().at(index).position.x };
			float terminal_y{ plane.GetVertices().at(index).position.y };

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

			// Get min value of overlap and compare between prev and current depth values
			float current_depth{ std::fmin(max_a - min_b, max_b - min_a) };

			if (prev_depth > current_depth) { prev_depth = current_depth; }

		}

	}

	// Multiply direction vector by depth penetration for object to be pushed by some depth amount
	push_vector *= prev_depth; // To be used out of func or within it

	//plane_a.Push(push_vector);
	//plane_b.Push(push_vector * 0.5f);

	return false;

}

// Circle-to-Polygon Collision
bool Collision::CircleToPolygon(const Plane& plane_a, const Plane& plane_b) {

	/* GOAL:
	* Create vector from circle center to closest vertices and check for overlap
	* [In case of overlap]:
	* Get orthogonal vector to some edge
	* Project vertices onto orthogonal vector
	* Get min and max vertices on orthogonal vector
	* Check if there is a gap between segments of plane a and plane b
	* Repeat for all edges
	*/

	std::vector<Plane> planes;

	// Create direction for plane_b to get pushed out of plane_a in case of collision
	Vector2 push_vector = Vector2::UnitVector(Vector2(plane_a.GetXPos(), plane_a.GetYPos(),
													  plane_b.GetXPos(), plane_b.GetYPos()));

	// Holds minimum amount to push pane_b out of plane_a
	float prev_depth{ INFINITY };

	// This is to make the first index of planes a circle and polygon 2nd (Lol)
	if (plane_a.IsPolygon()) {
	
		planes.push_back(plane_b);
		planes.push_back(plane_a);
	
	} else {

		planes.push_back(plane_a);
		planes.push_back(plane_b);

	}

	// Initialize x_0, y_0, x, and y values to make a displacement vector of one side
	float x_i{ planes.at(0).GetXPos() };
	float y_i{ planes.at(0).GetYPos() };

	float x_f{ 0.0f };
	float y_f{ 0.0f };

	float magnitude{ 0.0f };

	// for loop to find vertex from circle center position to closest vertices of polygon
	for (size_t i{ 1 }; i <= planes.at(1).GetNumSides(); ++i) {

		float x_tempf = planes.at(1).GetVertices().at(i).position.x;
		float y_tempf = planes.at(1).GetVertices().at(i).position.y;

		float other_magnitude{ Vector2::VectorMagnitude(Vector2(x_i, y_i, x_tempf, y_tempf)) };

		if ((i == 1) || (magnitude > other_magnitude)) {
		
			magnitude = other_magnitude;

			x_f = x_tempf;
			y_f = y_tempf;
		
		}

	}

	// Create axis of the vector
	Vector2 c_axis(Vector2::UnitVector(Vector2::GetOrthogonal(Vector2(x_i, y_i, x_f, y_f))));

	// Find min and max values of both plane_a and plane_b on axis
	std::pair<float, float> circle_plane{ FindMinMax(c_axis, planes.at(0)) };
	float min_a{ circle_plane.first };
	float max_a{ circle_plane.second };

	std::pair<float, float> polygon_plane{ FindMinMax(c_axis, planes.at(1)) };
	float min_b{ polygon_plane.first };
	float max_b{ polygon_plane.second };

	// Return true if no overlap between min and max values of plane_a and plane_b (no collision)
	if ((min_a < min_b && max_a <= min_b) ||
		(min_b < min_a && max_b <= min_a)) {

		return true;

	}

	// Get min value of overlap
	prev_depth = std::fmin(max_a - min_b, max_b - min_a);

	// Continue on to polygon to check for any overlaps (THIS IS A BIT OF A REPEAT FROM PolygonToPolygon(); CHANGE FOR LATER)
	for (size_t j{ 1 }; j < planes.at(1).GetVertices().size(); ++j) {

		// Initialize x_0, y_0, x, and y values to make a displacement vector of one side
		float init_x{ planes.at(1).GetVertices().at(j).position.x };
		float init_y{ planes.at(1).GetVertices().at(j).position.y };

		size_t index{ (j == static_cast<size_t>(planes.at(1).GetVertices().size() - 1)) ?
					  (((j + 1) % planes.at(1).GetVertices().size()) + 1) :
					  ((j + 1) % planes.at(1).GetVertices().size()) };

		float terminal_x{ planes.at(1).GetVertices().at(index).position.x };
		float terminal_y{ planes.at(1).GetVertices().at(index).position.y };

		// Get normal to displacement vector serving as axis
		Vector2 axis(Vector2::UnitVector(Vector2::GetOrthogonal(Vector2(init_x, init_y, terminal_x, terminal_y))));

		// Find min and max values of both plane_a and plane_b on axis
		std::pair<float, float> plane_a_min_max{ FindMinMax(axis, plane_a) };
		min_a = plane_a_min_max.first;
		max_a = plane_a_min_max.second;

		std::pair<float, float> plane_b_min_max{ FindMinMax(axis, plane_b) };
		min_b = plane_b_min_max.first;
		max_b = plane_b_min_max.second;

		// Return true if no overlap between min and max values of plane_a and plane_b (no collision)
		if ((min_a < min_b && max_a <= min_b) ||
			(min_b < min_a && max_b <= min_a)) {

			return true;

		}

		// Get min value of overlap and compare between prev and current depth values
		float current_depth{ std::fmin(max_a - min_b, max_b - min_a) };

		if (prev_depth > current_depth) { prev_depth = current_depth; }

	}

	// Multiply direction vector by depth penetration for object to be pushed by some depth amount
	push_vector *= prev_depth; // To be used out of func or within it

	//plane_a.Push(push_vector);
	//plane_b.Push(push_vector * 0.5f);

	return false;

}

// Circle-to-Circle Collision
bool Collision::CircleToCircle(const Plane& plane_a, const Plane& plane_b) {

	// Create direction for plane_b to get pushed out of plane_a in case of collision
	Vector2 push_vector = Vector2::UnitVector(Vector2(plane_a.GetXPos(), plane_a.GetYPos(),
													  plane_b.GetXPos(), plane_b.GetYPos()));
	
	// Add up the radius of the two circles
	float total_radius{ plane_a.GetRadius() + plane_b.GetRadius() };

	// Calculate the distance between the two center positions of the circles
	float distance{ sqrtf(powf((plane_a.GetXPos() - plane_b.GetXPos()), 2.0f) +
						  powf((plane_a.GetYPos() - plane_b.GetYPos()), 2.0f)) };

	// No collision occuring (true) if distance > total_radius
	if (distance > total_radius) { return true; }

	// Multiply direction vector by depth penetration for object to be pushed by some depth amount
	push_vector *= (total_radius - distance); // To be used out of func or within it

	//plane_a.Push(push_vector);
	//plane_b.Push(push_vector * 0.5f);

	return false;

}

// Returns a pair containing min and max value on some axis (min, max)
std::pair<float, float> Collision::FindMinMax(const Vector2& axis, const Plane& plane) {
	
	// Set min to some high positive value and max to low negative value
	float min{ INFINITY };
	float max{ -INFINITY };

	if (plane.IsPolygon()) {

		// Project all vertices onto the axis and reassign min and max to correct values
		for (size_t i{ 1 }; i < plane.GetVertices().size(); ++i) {

			float projection{ Vector2::Dot(Vector2(std::make_pair(plane.GetVertices().at(i).position.x, plane.GetVertices().at(i).position.y)), axis) };

			if (projection < min) { min = projection; }

			if (projection > max) { max = projection; }

		}

	} else {

		// Project center position of circle onto axis, then add the radius for max value, subtract for min value
		float center_projection{ Vector2::Dot(Vector2(std::make_pair(plane.GetXPos(), plane.GetYPos())), axis) };

		min = center_projection - plane.GetRadius();

		max = center_projection + plane.GetRadius();

	}

	return std::make_pair(min, max);

}
