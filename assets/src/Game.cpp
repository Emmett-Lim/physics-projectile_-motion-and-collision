#include "Game.h"

bool Game::Init() {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {

		std::cerr << "SDL failed to intialize! Error: " << SDL_GetError() << "\n";
		return false;

	}

	window_ = SDL_CreateWindow("Template_Name", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window_ == nullptr) {

		std::cerr << "Window failed to initialize! Error: " << SDL_GetError() << "\n";
		return false;

	}

	renderer_ = SDL_CreateRenderer(window_, -1, 0);
	if (renderer_ == nullptr) {

		std::cerr << "Renderer failed to initialize! Error: " << SDL_GetError() << "\n";
		return false;

	}

	int img_flags{ IMG_INIT_PNG };
	if (!(IMG_Init(img_flags) & img_flags)) {

		std::cerr << "SDL_Image failed to initialize! Error: " << IMG_GetError() << "\n";
		return false;

	}

	return true;

}

void Game::GameLoop() {

	float t{ 0.0f };
	const float dt{ 1 / 60.0f };

	timer_.Start();
	float initial_time{ timer_.GetElapsedTime() };
	float accumulator{ 0.0f };

	while (is_running_) {

		float final_time{ timer_.GetElapsedTime() };
		float frame_time{ final_time - initial_time };
		initial_time = final_time;

		accumulator += frame_time;

		HandleEvents();

		while (accumulator >= dt) {

			Update(t, dt);

			accumulator -= dt;
			t += dt; // Do I need this...?

		}

		Draw();

	}

}

void Game::HandleEvents() {

	SDL_Event e;

	while (SDL_PollEvent(&e)) {

		if (e.type == SDL_QUIT) {

			is_running_ = false;

		}

		mouse_.MouseHandleEvent(e, plane_b);

	}

	const Uint8* key_states = SDL_GetKeyboardState(nullptr);

	if (key_states[SDL_SCANCODE_ESCAPE]) {

		is_running_ = false;

	}

}

void Game::Update(float& t, const float dt) {

	/* Procedure:
	* Handle user events
	* Apply forces
	* Update position and velocity
	* Detect collisions
	* Solve constraints (work on after basic physics)
	*/

	if (mouse_.IsHoldingPolygon()) {

		plane_b.MouseMove(static_cast<float>(mouse_.GetMouseXPos()), static_cast<float>(mouse_.GetMouseYPos()));

	}

	plane_a.Move(dt);
	plane_b.Move(dt);

	/* TEST FOR SAT COLLISION (IT WORKS!)
	if (!Collision::CheckCollision(plane_b, plane_a)) { std::cout << "Collision found!\n"; }
	else { std::cout << "No Collision!\n"; }
	*/

	Vector2 mt_vector;

	if (!Collision::CheckCollision(plane_b, plane_a, mt_vector)) {
	
		// Test
		//std::cout << "Collision found!\n";
		plane_a.Push(mt_vector * 0.5f);
		plane_b.Push(mt_vector * -0.5f);
	
	} else {
	
		// Test
		//std::cout << "No Collision!\n";
		
	}

}

void Game::Draw() {

	SDL_SetRenderDrawColor(renderer_, 40, 40, 40, 225);
	SDL_RenderClear(renderer_);

	/*
	for (int i = 0; i < 25; i++) {
		float angle = ((2 * M_PI / 25) * i);
		float x = plane_a.GetXPos() + plane_a.GetRadius() * cos(angle);
		float y = plane_a.GetYPos() + plane_a.GetRadius() * sin(angle);

		SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
		SDL_RenderDrawPointF(renderer_, x, y);
	}

	SDL_RenderGeometry(renderer_, texture_, plane_b.GetVertices().data(), (plane_b.GetNumSides() + 1), plane_b.GetIndices().data(), (plane_b.GetNumSides() * 3));
	*/

	SDL_RenderGeometry(renderer_, texture_, plane_a.GetVertices().data(),
					   plane_a.GetVertices().size(), plane_a.GetIndices().data(), plane_a.GetIndices().size()); // Test as non-interactable obj
	SDL_RenderGeometry(renderer_, texture_, plane_b.GetVertices().data(),
					   plane_b.GetVertices().size(), plane_b.GetIndices().data(), plane_b.GetIndices().size()); // Test interactable obj

	SDL_RenderPresent(renderer_);

}

void Game::Close() {

	SDL_DestroyTexture(texture_);
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);

	IMG_Quit();
	SDL_Quit();

}