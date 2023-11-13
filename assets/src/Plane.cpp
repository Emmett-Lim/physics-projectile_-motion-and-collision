#include "Plane.h"

Plane::Plane(const float& xpos, const float& ypos, const float& radius, const int& vertices, bool is_static) {

	this->xpos_ = xpos;
	this->ypos_ = ypos;
	this->radius_ = radius;
	this->is_static_ = is_static;

	// Assume vertices value of 0 or 1 is a circle, 2 is semi-circle, 3 or more is a polygon
	if (vertices > 1) {

		this->indices_ = new int[vertices];
	}

	if (vertices > 2) {

		this->vertices_ = new SDL_Vertex[vertices];

		for (int i{ 0 }; i < vertices; ++i) {

			float angle{ this->rad_ * i / vertices };

			float x_vertexpos{ this->xpos_ + this->radius_ * cos(angle) };
			float y_vertexpos{ this->xpos_ + this->radius_ * sin(angle) };

			SDL_Vertex vertex{ { x_vertexpos, y_vertexpos }, { 255, 255, 255 }, { 1, 1 } };
			this->vertices_[i] = vertex;

			this->vertex_pos_.push_back({ x_vertexpos, y_vertexpos });

			this->indices_[i] = i;
		}
		// semi-circle will require a special rotation
	} else if (vertices == 2) {

		for (int i{ 0 }; i < 2; ++i) {

			float x_vertexpos{ this->xpos_ + ((i * -1) * this->radius_ * cos(this->rad_)) };
			float y_vertexpos{ this->xpos_ + ((i * -1) * this->radius_ * sin(this->rad_)) };

			this->vertex_pos_.push_back({ x_vertexpos, y_vertexpos });

			this->indices_[i] = i;
		}
	}
}

Plane::~Plane() {

	if (this->vertices_ != nullptr) { delete this->vertices_; }

	if (this->indices_ != nullptr) { delete this->indices_; }
}