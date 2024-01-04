#pragma once

#include "utilities.h"
#include "Plane.h"
#include "Mouse.h"
#include "Collision.h"
#include "Time.h"

class Game {

	private:
	
		void HandleEvents();
		void Update(float& t, const float dt, float& accumulator);
		void Draw();
	
		bool is_running_{ true };
	
		SDL_Window* window_{ nullptr };
		SDL_Renderer* renderer_{ nullptr };
		SDL_Texture* texture_{ nullptr };
	
		Time timer_;
		Mouse mouse_;
	
		// Test Instances:
		Plane plane_a{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 57.0, 3, false };
		Plane plane_b{ SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3, 50.0, 5, false };
	
	public:
	
		bool Init();
		void GameLoop();
		void Close();

};