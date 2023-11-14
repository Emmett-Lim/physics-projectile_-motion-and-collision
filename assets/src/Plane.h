#pragma once

#include "utilities.h"

class Plane {

	private:

		SDL_Vertex *vertices_{ nullptr };					// dynamic array that will contain SDL_Vertex points (as long as it is a polygon)
		int *indices_{ nullptr };							// this connects all the vertex in order (optional tbh)
		std::vector<std::pair<float, float>> vertex_pos_;	// pair container to store pos of vertices (two "vertices" for semi-circle, none for circles)

		float xpos_, ypos_, radius_;
		int num_sides_, total_points_, num_indices_;		// total sides of polygon, total amnt of vertices, amount of points (in 3's) to make a triangle of the polygon
		float rad_{ 2.0f * static_cast<float>(M_PI) };		// not sure if I will need this so it's here for now
		bool is_static_;

	public:

		Plane(const float& xpos = (SCREEN_WIDTH / 2), const float& ypos = (SCREEN_HEIGHT / 2),
			  const float& radius = 5, const int &vertices = 0, bool is_static = false);
		~Plane();

		SDL_Vertex* GetVertices() { return this->vertices_; }

		int* GetIndices() { return this->indices_; }

		const std::vector<std::pair<float, float>>& GetVertexPos() { return this->vertex_pos_; }

		const float& GetXPos() { return this->xpos_; }
		const float& GetYPos() { return this->ypos_; }

		const float& GetRadius() { return this->radius_; }

		const int& GetNumSides() { return this->num_sides_; }
		const int& GetTotalPoints() { return this->total_points_; }
		const int& GetNumIndices() { return this->num_indices_; }

		const bool& IsStatic() { return this->is_static_; }
};