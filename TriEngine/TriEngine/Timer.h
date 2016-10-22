#ifndef TIMER_H
#define TIMER_H

#include <GLFW\glfw3.h>

namespace TriEngine {

	class Timer {

	private:
		unsigned int prevTicks;
		unsigned int currTicks;

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
		float GetDeltaTime() const;
		unsigned int GetSleepTime(const unsigned int fps) const;
	};

}
#endif
