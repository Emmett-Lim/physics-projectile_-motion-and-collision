#pragma once

#include "utilities.h"
#include "Vector2.h"

class Plane {

	private:
		
		// Plane vertices for a polygon
		std::vector<SDL_Vertex> vertices_; // contains all vertices of a polygon
		std::vector<int> indices_; //contains an order of how to form a polygon based on vertices

		// Defines the shape of a polygon, including circles
		float radius_;
		int num_sides_;
		float rad_{ 2.0f * static_cast<float>(M_PI) };
		
		// Plane properties
		float xpos_, ypos_; // Center position of a shape
		float mass_;
		Vector2 linear_vel_;
		Vector2 force_;
		const float gravity_{ 9.81f }; // Will not apply to user-held and static planes

		/* Implement Later:
		* Vector2 angular_vel_;
		* Vector2 torque_;
		* float angle_;
		*/

		// Checkers for type of plane
		bool is_static_; // Static object meaning doesn't move even when external forces are applied to it
		bool being_held_;
		bool is_polygon_;

	public:

		Plane(const float& xpos = (SCREEN_WIDTH / 2), const float& ypos = (SCREEN_HEIGHT / 2),
			  const float& radius = 5, const int &vertices = 0, bool is_static = false);

		const std::vector<SDL_Vertex>& GetVertices() const { return this->vertices_; }

		const std::vector<int>& GetIndices() const { return this->indices_; }

		const float GetXPos() const { return this->xpos_; }
		const float GetYPos() const { return this->ypos_; }

		const int GetNumSides() const { return this->num_sides_; }
		const float GetRadius() const { return this->radius_; }

		const float GetMass() const { return this->mass_; }

		const bool IsStatic() const { return this->is_static_; }

		const bool BeingHeld() const { return this->being_held_; }
		void SetHold(bool being_held) { this->being_held_ = being_held; }

		const bool IsPolygon() const { return this->is_polygon_; }

		void Move(const float dt);
		void MouseMove(const float& m_xcoord, const float& m_ycoord);

};