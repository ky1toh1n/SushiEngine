#include "InputManager.h"

namespace SushiEngine
{
	/* ---- STATIC ---- */
	InputManager* InputManager::instance = nullptr; 

	void InputManager::KeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
	{
		//Update state
		instance->keyData[key] = action;

		//Print to console
		if (action == GLFW_PRESS)
		{
			cout << "Keypressed: " << char(key) << endl;
		}
		else if (action == GLFW_RELEASE)
		{
			cout << "Released: " << char(key) << endl;
		}
		else if (action == GLFW_REPEAT)
		{
			cout << "Repeated: " << char(key) << endl;
		}
	}

	void InputManager::ClickCallback(GLFWwindow* glfwWindow, int button, int action, int mods)
	{
		cout << "Click: " << endl;
	}

	void InputManager::MouseMoveCallback(GLFWwindow * glfwWindow, double x, double y)
	{
		instance->mouseX = x;
		instance->mouseY = y;
	}
	/* ---- End of STATIC ---- */
	/* ---- INSTANCE ---- */
	InputManager::InputManager()
	{
		Debug::Log(EMessageType::S_INFO, "\tInputManager()", __FILENAME__, __LINE__);
		if (instance == nullptr)
		{
			instance = this;
		}
		else
		{
			Debug::Log(EMessageType::S_WARNING, "\tInputManager() - More than one InputManager has been created.", __FILENAME__, __LINE__);
		}
	}

	InputManager::~InputManager()
	{
		Debug::Log(EMessageType::S_INFO, "\t~InputManager()", __FILENAME__, __LINE__);
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
	/* ---- End of INSTANCE ---- */
}