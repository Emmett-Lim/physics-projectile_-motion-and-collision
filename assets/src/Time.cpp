#include "Time.h"

// Function that starts timer and resumes after being paused
void Time::Start() {

	this->has_started_ = true;

	this->time_passed_ = SDL_GetTicks64();

}

// Pauses Timer and saves ticks accumulated since start of timer
void Time::Pause() {

	if (this->has_started_) {

		this->has_started_ = false;

		// We get current accumulated ticks minus previous accumulated ticks when timer started
		// to get actual amount of ticks accumulated
		this->time_passed_ = SDL_GetTicks64() - this->time_passed_;

	}

}

// Reset the timer
void Time::Reset() {

	this->has_started_ = false;

	this->time_passed_= 0;

}