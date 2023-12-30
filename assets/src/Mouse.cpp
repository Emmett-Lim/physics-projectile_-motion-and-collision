#include "Mouse.h"

void Mouse::MouseHandleEvent(SDL_Event& e, Plane& plane) {
	
	// Stores mouse coordinates every frame if there is a detectable event
	SDL_GetMouseState(&this->m_x_pos_, &this->m_y_pos_);

	if (e.type == SDL_MOUSEBUTTONDOWN) {

		if (e.button.button == SDL_BUTTON_LEFT &&
		   (sqrtf(powf((static_cast<float>(this->m_x_pos_) - plane.GetVertices().at(0).position.x), 2.0f) +
				  powf((static_cast<float>(this->m_y_pos_) - plane.GetVertices().at(0).position.y), 2.0f))) <
		   this->m_radii_ + plane.GetRadius()) {

			this->holding_polygon_ = true;

		} else if (e.button.button == SDL_BUTTON_RIGHT) {

			//this->holding_polygon_ = true;
			// Print coordinates of center of a polygon (Temporary)
			std::cout << "Plane center coords: (" << plane.GetVertices().at(0).position.x << ", " << plane.GetVertices().at(0).position.y << ")\n";

		}

	}
	else if (e.type == SDL_MOUSEBUTTONUP) {

		this->holding_polygon_ = false;

	}

}