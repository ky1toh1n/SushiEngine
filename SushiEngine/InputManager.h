/** Stores the current state of the keyboard and mouse. */
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
/* System */
#include <memory>
/* Third Party */
#include "GLFW/glfw3.h"
/* SushiEngine */
#include "Macros.h"
#include "Debug.h"
/* ---- */
namespace SushiEngine
{
	class SceneContext;
	class InputManager
	{
	public:
		/* Instance methods */
		bool isKeyDown(int key);
		void getMousePosition(double*, double*);
		void getMouseDragDifference(double*, double*);
		bool isMouseOutsideWindow();
	private:
		// Allow this class to instantiate InputManager.
		friend SceneContext;

		/* Constructor */
		InputManager();
		~InputManager();

		/* Instance fields */ 
		int mKeyData[GLFW_KEY_LAST];	
		double mMouseX=-1;
		double mMouseY=-1;
		bool mIsMouseOutsideOfScreen=true;
		//Draggin'
		bool mMouseDragOn = false;
		double mStartDragX=-1;
		double mStartDragY = -1;

		/* Static fields*/
		static InputManager* sInstance;

		/* Static methods */
		//GLFW Callbacks
		static void KeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
		static void ClickCallback(GLFWwindow* glfwWindow, int button, int action, int mods);
		static void MouseMoveCallback(GLFWwindow *, double, double);
		static void WindowEnterCallback(GLFWwindow* window, int entered);
	};
}
#endif INPUT_MANAGER_H