#pragma once

#include "utilities.h"

class Plane {

	private:
		
		std::vector<SDL_Vertex> vertices_;					// vector that contains SDL_Vertex points (only for polygon)
		std::vector<int> indices_;							// vector containing numbers representing indices of a triangle connected together to form a polygon
		std::vector<std::pair<float, float>> vertex_pos_;	// pair container to store pos of vertices (two "vertices" for semi-circle, none for circles)

		float xpos_, ypos_, radius_;
		int num_sides_, total_points_, num_indices_;		// total sides of polygon, total amnt of vertices, amount of points (in 3's) to make a triangle of the polygon
		float rad_{ 2.0f * static_cast<float>(M_PI) };		// not sure if I will need this so it's here for now
		bool is_static_;

	public:

		Plane(const float& xpos = (SCREEN_WIDTH / 2), const float& ypos = (SCREEN_HEIGHT / 2),
			  const float& radius = 5, const int &vertices = 0, bool is_static = false);
		~Plane();

		const std::vector<SDL_Vertex>& GetVertices() const { return this->vertices_; }

		const std::vector<int>& GetIndices() const { return this->indices_; }

		const std::vector<std::pair<float, float>>& GetVertexPos() const { return this->vertex_pos_; }

		const float& GetXPos() const { return this->xpos_; }
		const float& GetYPos() const { return this->ypos_; }

		const float& GetRadius() const { return this->radius_; }

		const int& GetNumSides() const { return this->num_sides_; }
		const int& GetTotalPoints() const { return this->total_points_; }
		const int& GetNumIndices() const { return this->num_indices_; }

		const bool& IsStatic() const { return this->is_static_; }
};