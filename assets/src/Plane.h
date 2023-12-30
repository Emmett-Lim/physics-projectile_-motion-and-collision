#pragma once

#include "utilities.h"

class Plane {

	private:
		
		// std::vector<SDL_Vertex> for containing all vertices of a polygon
		std::vector<SDL_Vertex> vertices_;

		// std::vector<int> containing an order of how to form a polygon based on points
		std::vector<int> indices_;

		// std::vector<std::pair<float, float>> to store coordinates of the points (might not be needed)
		std::vector<std::pair<float, float>> vertex_pos_;

		float xpos_, ypos_;

		float radius_;
		int num_sides_;
		float rad_{ 2.0f * static_cast<float>(M_PI) };
		
		float mass_;
		float const_speed_;

		bool is_static_;

		bool is_polygon_;

	public:

		Plane(const float& xpos = (SCREEN_WIDTH / 2), const float& ypos = (SCREEN_HEIGHT / 2),
			  const float& radius = 5, const int &vertices = 0, bool is_static = false);

		const std::vector<SDL_Vertex>& GetVertices() const { return this->vertices_; }

		const std::vector<int>& GetIndices() const { return this->indices_; }

		const std::vector<std::pair<float, float>>& GetVertexPos() const { return this->vertex_pos_; }

		const float GetXPos() const { return this->xpos_; }
		const float GetYPos() const { return this->ypos_; }

		const int GetNumSides() const { return this->num_sides_; }
		const float GetRadius() const { return this->radius_; }

		const float GetMass() const { return this->mass_; }
		const float GetSpeed() const { return this->const_speed_; }

		const bool IsStatic() const { return this->is_static_; }
		const bool IsPolygon() const { return this->is_polygon_; }

		void Move(const float& dx, const float& dy);
		void MouseMove(const float& m_xcoord, const float& m_ycoord);

};