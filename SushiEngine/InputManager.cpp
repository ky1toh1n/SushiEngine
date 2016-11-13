#include "InputManager.h"


namespace SushiEngine 
{
	/// See the header file reguarding unique_ptr
	std::unique_ptr<InputManager> InputManager::instance(nullptr);

	InputManager::InputManager()
	{

	}

	InputManager::~InputManager()
	{

	}

	InputManager* InputManager::GetInstance() 
	{
		if (instance == nullptr)
		{
			instance.reset(new InputManager());
		}
		return instance.get();
	}

	void InputManager::KeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) 
	{
		//Update state
		GetInstance()->keyData[key] = action;

		//Print to console
		if (action == GLFW_PRESS) 
		{
			std::cout << "Keypressed: " << char(key) << std::endl;
		}
		else if (action == GLFW_RELEASE)
		{
			std::cout << "Released: " << char(key) << std::endl;
		}
		else if (action == GLFW_REPEAT) 
		{
			std::cout << "Repeated: " << char(key) << std::endl;
		}
	}

	void InputManager::ClickCallback(GLFWwindow* glfwWindow, int button, int action, int mods) 
	{
		std::cout << "Click: " << std::endl;
	}


	void InputManager::MouseMoveCallback(GLFWwindow * glfwWindow, double x, double y)
	{
		InputManager * input = InputManager::GetInstance();
		input->mouseX = x;
		input->mouseY = y;
	}
	
	bool InputManager::isKeyDown(int key)
	{
		return keyData[key] == GLFW_PRESS || keyData[key] == GLFW_REPEAT;
	}


	void InputManager::getMousePosition(double* xRef, double* yRef)
	{
		*xRef = mouseX;
		*yRef = mouseY;
	}
}