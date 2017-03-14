#include "Timer.h"

namespace SushiEngine
{

	Timer::Timer() :prevTicks(0), currTicks(0) 
	{
	
	}

	Timer::~Timer() 
	{
	
	}
	
	// Initializes the timer.
	void Timer::start() 
	{
		prevTicks = glfwGetTime();
		currTicks = glfwGetTime();
	}

	// Updates the timer and returns the resulting DeltaTime.
	double Timer::update()
	{
		prevTicks = currTicks;
		currTicks = glfwGetTime();

		return (currTicks - prevTicks);
	}
}