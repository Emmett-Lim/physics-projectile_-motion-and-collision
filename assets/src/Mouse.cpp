#include "Mouse.h"

void Mouse::MouseHandleEvent(SDL_Event& e) {
	
	SDL_GetMouseState(&this->m_x_pos_, &this->m_y_pos_);

	if (e.type == SDL_MOUSEBUTTONDOWN) {

		if (e.button.button == SDL_BUTTON_LEFT) {

			

		} else if (e.button.button == SDL_BUTTON_RIGHT) {

			

		}

	}

}