#pragma once

#include "utilities.h"

class Vector2 {

	private:
		
		std::pair<float, float> direction_;
	
	public:

		Vector2(float x_init = 0.0f, float y_init = 0.0f, float x_final = 1.0f, float y_final = 1.0f)
			: direction_{ (x_final - x_init), (y_final - y_init) } {}

		Vector2(std::pair<float, float> direction) : direction_{ direction } {}

		Vector2(const Vector2& other) : direction_(other.direction_) {}

		const std::pair<float, float>& GetDirection() const { return this->direction_; }

		static float Dot(const Vector2& a, const Vector2& b) {

			return ((a.direction_.first * b.direction_.first) +
					(a.direction_.second * b.direction_.second));

		}

		static float Cross(const Vector2& a, const Vector2& b) {

			return ((a.direction_.first * b.direction_.second) -
					(a.direction_.second * b.direction_.first));

		}

		static float VectorMagnitude(const Vector2& a) {

			return sqrtf((a.direction_.first * a.direction_.first) +
						 (a.direction_.second * a.direction_.second));

		}

		static Vector2 UnitVector(const Vector2& a) {

			float magnitude{ VectorMagnitude(a) };
			return Vector2{ std::make_pair((a.direction_.first / magnitude), (a.direction_.second / magnitude)) };

		}

		static Vector2 GetOrthogonal(const Vector2& a) {

			return Vector2{ std::make_pair(-a.direction_.second, a.direction_.first) };

		}

		bool operator==(const Vector2& other) const {

			return ((this->direction_.first == other.direction_.first) &&
					(this->direction_.second == other.direction_.second));

		}

		bool operator!=(const Vector2& other) const {

			return !(*this == other);

		}

		Vector2 operator+(const Vector2& other) const {

			return Vector2{ std::make_pair((this->direction_.first + other.direction_.first),
										   (this->direction_.second + other.direction_.second)) };

		}

		Vector2 operator-(const Vector2& other) const {

			return Vector2{ std::make_pair((this->direction_.first - other.direction_.first),
										   (this->direction_.second - other.direction_.second)) };

		}

		Vector2 operator*(const float scalar) {

			return Vector2{ std::make_pair((this->direction_.first * scalar), (this->direction_.second * scalar)) };

		}

		Vector2 operator/(const float scalar) {

			return Vector2{ std::make_pair((this->direction_.first / scalar), (this->direction_.second / scalar)) };

		}

		Vector2& operator=(const Vector2& other) {

			if (*this != other) { this->direction_ = other.direction_; }

			return *this;

		}

		void operator+=(const Vector2& other) { *this = (*this + other); }

		void operator-=(const Vector2& other) { *this = (*this - other); }

		void operator*=(const float scalar) { *this = (*this * scalar); }

		void operator/=(const float scalar) { *this = (*this / scalar); }

};