#pragma once

#include "utilities.h"

class Game {

private:

	void HandleEvents();
	void Update();
	void Draw();

	bool is_running_{ true };

	SDL_Window* window_{ nullptr };
	SDL_Renderer* renderer_{ nullptr };
	SDL_Texture* texture_{ nullptr };

public:

	bool Init();
	void GameLoop();
	void Close();
};