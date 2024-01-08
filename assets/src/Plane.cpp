#include "Plane.h"

Plane::Plane(const float& xpos, const float& ypos, const float& radius, const int& vertices, bool is_static) {

	this->xpos_ = xpos;
	this->ypos_ = ypos;

	this->radius_ = radius;

	this->is_static_ = is_static;
	this->being_held_ = false;
	this->is_polygon_ = true;

	if (vertices < 3) {

		// Create a triangle if num vertices less than 3
		this->num_sides_ = 3;

	} else if (vertices > 10) {

		// Create a circle if vertices > 10
		this->num_sides_ = static_cast<int>(floor((2 * M_PI * radius) + 1));
		this->is_polygon_ = false;

	} else {

		// Leave vertices alone to make a polygon
		this->num_sides_ = vertices;

	}

	this->mass_ = radius * 10.0f; // Temporary mass value

	// Vertices value <= 3 is triangle, greater than 3 is a polygon, greater than 10 approximates to a circle

	// Vertex at index 0 of vertices array is the position of center of polygon.
	this->vertices_.push_back({ { this->xpos_, this->ypos_ }, { 255, 255, 255, 255 }, { 1, 1 } });

	for (int i{ 1 }; i <= this->num_sides_; ++i) {

		// Calculate inner angles of a polygon based on number of sides, then place points regarding the angle
		float angle{ (this->rad_ / this->num_sides_) * i };

		float x_vertexpos{ this->xpos_ + this->radius_ * cos(angle) };
		float y_vertexpos{ this->ypos_ + this->radius_ * sin(angle) };

		// Push all vertices into std::vector for drawing onto window
		this->vertices_.push_back({ { x_vertexpos, y_vertexpos }, { 255, 255, 255, 255 }, { 1, 1 } });

		// Form a triangle with three points, main point being the center of a polygon
		this->indices_.push_back(0);
		this->indices_.push_back(i);
		this->indices_.push_back((i % this->num_sides_) + 1);

	}
}

void Plane::Move(const float dt) {

	if (!this->is_static_ && !this->being_held_) {

		// Look back at Game.cpp to see Physics procedure

		this->xpos_ += this->linear_vel_.GetDirection().first * dt;
		this->ypos_ += this->linear_vel_.GetDirection().second * dt;

	}

}

void Plane::Push(const Vector2 push) {

	this->xpos_ += push.GetDirection().first;
	this->ypos_ += push.GetDirection().second;

	for (size_t i{ 0 }; i < this->vertices_.size(); ++i) {

		this->vertices_.at(i).position.x += push.GetDirection().first;
		this->vertices_.at(i).position.y += push.GetDirection().second;

	}

}

void Plane::MouseMove(const float m_xcoord, const float m_ycoord) {

	float x_diff{ m_xcoord - this->vertices_.at(0).position.x };
	float y_diff{ m_ycoord - this->vertices_.at(0).position.y };

	this->Push(Vector2(std::make_pair(x_diff, y_diff)));

}