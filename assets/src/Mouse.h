#pragma once

#include "utilities.h"
#include "Plane.h"

class Mouse {

	private:

		int m_x_pos_, m_y_pos_;				// Stores mouse position if within window (SDL2 can only get int value of mouse coords)
		const float m_radii_;				// Placeholder
		bool holding_polygon_;				// Placeholder

	public:

		Mouse() : m_x_pos_(0), m_y_pos_(0), m_radii_(10), holding_polygon_(false) {};

		const int GetMouseXPos() const { return this->m_x_pos_; }
		const int GetMouseYPos() const { return this->m_y_pos_; }

		const float GetMouseRadii() const { return this->m_radii_; }

		const bool IsHoldingPolygon() const { return this->holding_polygon_; }

		void MouseHandleEvent(SDL_Event &e, Plane &plane);

};