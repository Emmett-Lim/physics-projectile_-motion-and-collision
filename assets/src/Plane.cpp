#include "Plane.h"

Plane::Plane(const float& xpos, const float& ypos, const float& radius, const int& vertices, bool is_static) {

	this->xpos_ = xpos;
	this->ypos_ = ypos;

	this->radius_ = radius;

	this->is_static_ = is_static;

	this->num_sides_ = vertices;

	this->mass_ = radius * 10.0f;																				// Temporary mass value
	this->const_speed_ = 8.0f;

	// Assume vertices value of 0 or 1 is a circle, 2 is semi-circle, 3 or more is a polygon

	if (vertices > 2) {

		this->vertices_.push_back({ { this->xpos_, this->ypos_ }, { 255, 255, 255, 255 }, { 1, 1 } });			// Vertex at index 0 of vertices array is the position of center of polygon.
		
		for (int i{ 1 }; i <= this->num_sides_; ++i) {

			float angle{ (this->rad_ / this->num_sides_) * i };													// angle formed by circumference of circle divided by num of sides of polygon times i

			float x_vertexpos{ this->xpos_ + this->radius_ * cos(angle) };										// (x, y) coords for each vertex
			float y_vertexpos{ this->ypos_ + this->radius_ * sin(angle) };

			this->vertices_.push_back({ { x_vertexpos, y_vertexpos }, { 255, 255, 255, 255 }, { 1, 1 } });		// Create vertex object with created (x, y) coords and store into vertices container

			this->vertex_pos_.push_back({ x_vertexpos, y_vertexpos });											// Store vertex coords into vertex_pos container for collision checking

			this->indices_.push_back(0);																		// Connects 2 vertices to center of polygon w/ respect to vertices container
			this->indices_.push_back(i);																		// (i.e. value 0 is the center of polygon, connecting with current value i the
			this->indices_.push_back((i % this->num_sides_) + 1);												// loop is on and the next vertex ((i % this->num_sides_) + 1))
																												// (i % this->num_sides_) + 1) ensures that the index is within the range
			if (i == this->num_sides_) {																		// of valid vertices, and it wraps around to 1 for the last vertex.

				this->indices_.push_back(1);																	// This line sets the third element of the set of three indices to 1,
																												// completing the wrap-around for the last triangle
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

	
}

void Plane::Move(const float& dx, const float& dy) {

	

}

void Plane::MouseMove(const float& m_xcoord, const float& m_ycoord) {

	float x_diff{ m_xcoord - this->vertices_.at(0).position.x };
	float y_diff{ m_ycoord - this->vertices_.at(0).position.y };

	for (size_t i{ 0 }; i < this->vertices_.size(); ++i) {

		this->vertices_.at(i).position.x += x_diff;
		this->vertices_.at(i).position.y += y_diff;

		if ((i > 0) && (i < this->vertex_pos_.size())) {

			this->vertex_pos_.at(i - 1).first += x_diff;
			this->vertex_pos_.at(i - 1).second += y_diff;

		}

	}

}