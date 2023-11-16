#include "Plane.h"

Plane::Plane(const float& xpos, const float& ypos, const float& radius, const int& vertices, bool is_static) {

	this->xpos_ = xpos;
	this->ypos_ = ypos;

	this->radius_ = radius;

	this->is_static_ = is_static;

	this->num_sides_ = vertices;
	this->total_points_ = vertices + 1;
	this->num_indices_ = vertices * 3;

	// Assume vertices value of 0 or 1 is a circle, 2 is semi-circle, 3 or more is a polygon

	if (vertices > 2) {

		this->vertices_ = new SDL_Vertex[this->total_points_];													// Creates dynamic array of vertices along with the center of polygon.
		this->indices_ = new int[this->num_indices_];															// Dynamic array for setting triangles to form shape of polygon.

		this->vertices_[0] = { { this->xpos_, this->ypos_ }, { 255, 255, 255, 255 }, { 1, 1 } };				// Vertex at index 0 of vertices array is the position of center of polygon.

		for (int i{ 1 }; i <= this->num_sides_; ++i) {

			float angle{ (this->rad_ / this->num_sides_) * i };													// angle formed by circumference of circle divided by num of sides of polygon times i

			float x_vertexpos{ this->xpos_ + this->radius_ * cos(angle) };										// (x, y) coords for each vertex
			float y_vertexpos{ this->ypos_ + this->radius_ * sin(angle) };

			if (i < this->total_points_) {
				this->vertices_[i] = { { x_vertexpos, y_vertexpos }, { 255, 255, 255, 255 }, { 1, 1 } };		// Create vertex object with created (x, y) coords and store into vertices container
			}

			this->vertex_pos_.push_back({ x_vertexpos, y_vertexpos });											// Store vertex coords into vertex_pos container for collision checking

			if ((i * 3) <= this->num_indices_) {
				this->indices_[(i - 1) * 3] = 0;																// Connects 2 vertices to center of polygon w/ respect to vertices container
				this->indices_[(i - 1) * 3 + 1] = i;															// (i.e. value 0 is the center of polygon, connecting with current value i the
				this->indices_[(i - 1) * 3 + 2] = (i % this->num_sides_) + 1;									// loop is on and the next vertex ((i % this->num_sides_) + 1))
																												// (i % this->num_sides_) + 1) ensures that the index is within the range
				if (i == this->num_sides_) {																	// of valid vertices, and it wraps around to 1 for the last vertex.

					this->indices_[(i - 1) * 3 + 2] = 1;														// This line sets the third element of the set of three indices to 1,
				}																								// completing the wrap-around for the last triangle
			}
		}

	} else if (vertices == 2) {																					// W.I.P.

		for (int i{ 0 }; i < 2; ++i) {

			float x_vertexpos{ this->xpos_ + ((i * -1) * this->radius_ * cos(this->rad_)) };
			float y_vertexpos{ this->ypos_ + ((i * -1) * this->radius_ * sin(this->rad_)) };

			this->vertex_pos_.push_back({ x_vertexpos, y_vertexpos });
		}

	}
}

Plane::~Plane() {

	if (this->vertices_ != nullptr) { delete[] this->vertices_; }

	if (this->indices_ != nullptr) { delete[] this->indices_; }
}