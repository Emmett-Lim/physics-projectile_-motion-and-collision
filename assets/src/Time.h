#pragma once

#include "utilities.h"

class Time {

	private:

		Uint64 time_passed_;

		bool has_started_;

	public:

		Time() : time_passed_(0), has_started_(false) {}

		// Basic functions for how a timer works
		void Start();
		void Pause();
		void Reset();

		// Returns elapsed time in seconds
		const float GetElapsedTime() const {

			return ((this->has_started_) ? ((SDL_GetTicks64() - this->time_passed_) / 1000.0f)
										 : (this->time_passed_ / 1000.0f));

		}

		// Returns whether if timer is running or not
		const bool IsPaused() const { return this->has_started_; }

};