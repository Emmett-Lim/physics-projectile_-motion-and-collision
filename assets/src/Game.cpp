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

	while (is_running_) {

		HandleEvents();
		Update();
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

void Game::Update() {

	if (mouse_.IsHoldingPolygon()) {

		plane_b.MouseMove(static_cast<float>(mouse_.GetMouseXPos()), static_cast<float>(mouse_.GetMouseYPos()));

	}

	/* TEST FOR SAT COLLISION (IT WORKS!)
	if (!Collision::PolygonToPolygon(plane_b, plane_a)) { std::cout << "Collision found!\n"; }
	else { std::cout << "No Collision!\n"; }
	*/
	
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

	SDL_RenderGeometry(renderer_, texture_, plane_a.GetVertices().data(), (plane_a.GetNumSides() + 1), plane_a.GetIndices().data(), (plane_a.GetNumSides() * 3));		// Test as non-interactable obj
	SDL_RenderGeometry(renderer_, texture_, plane_b.GetVertices().data(), (plane_b.GetNumSides() + 1), plane_b.GetIndices().data(), (plane_b.GetNumSides() * 3));		// Test interactable obj

	SDL_RenderPresent(renderer_);

}

void Game::Close() {

	SDL_DestroyTexture(texture_);
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);

	IMG_Quit();
	SDL_Quit();

}