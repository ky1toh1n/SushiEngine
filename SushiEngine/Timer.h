/** A simple timer - keeps track of delta time through GLFW. */ 
#ifndef TIMER_H
#define TIMER_H
/* System */
/* Third Party */
#include <GLFW\glfw3.h>
/* SushiEngine */
#include "Macros.h"
/* ---- */
namespace SushiEngine 
{
	class Timer 
	{
	public:
		/* Constructor */
		Timer();
		~Timer();
		NO_COPY_CONSTRUCTORS(Timer)

		/* Instance Methods */
		void start();
		double update();
	private:
		/* Instance Fields */
		double prevTicks;
		double currTicks;
	};
}
#endif
