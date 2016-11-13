//TIMER - Keeps track of the time. 
#ifndef TIMER_H
#define TIMER_H

#include <GLFW\glfw3.h>

namespace SushiEngine 
{
	class Timer {
	public:
		Timer();
		~Timer();

		/// C11 precautions
		Timer(const Timer&) = delete;
		Timer(Timer&&) = delete;
		Timer& operator=(const Timer&) = delete;
		Timer& operator=(Timer&&) = delete;

		void Start();
		void UpdateFrameTicks();
		double GetDeltaTime() const;
		unsigned int GetSleepTime(const unsigned int fps) const;

	private:
		double prevTicks;
		double currTicks;
	};
}
#endif
