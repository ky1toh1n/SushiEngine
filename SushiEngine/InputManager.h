//INPUT MANAGER - stores the current state of the keyboard and mouse. Uses GLFW callbacks.
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <memory>
#include "GLFW/glfw3.h"
#include "Debug.h"

namespace SushiEngine {

	class InputManager
	{
	private:
		///std::unique_ptr is a smart pointer that destroys the object it point to when the unique_ptr goes out of scope.
		static std::unique_ptr<InputManager> instance;

		/// Since my destructor is private the template std::unique_ptr needs access so I made it a friend.
		/// However, std::default_delete is the default destruction policy used by std::unique_ptr 
		/// when no deleter is specified, therefore I'll make std::default_delete my friend as well. 
		friend std::default_delete<InputManager>;

		//Private constructor
		InputManager();
		~InputManager();

		int keyData[GLFW_KEY_LAST];	
		double mouseX=-1;
		double mouseY=-1;
	public:
		//
		bool isKeyDown(int key);
		void getMousePosition(double*, double*);

		//Public methods
		static InputManager* GetInstance();
		//Callbacks
		static void KeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
		static void ClickCallback(GLFWwindow* glfwWindow, int button, int action, int mods);
		static void MouseMoveCallback(GLFWwindow *, double, double);
	};
}
#endif INPUT_MANAGER_H