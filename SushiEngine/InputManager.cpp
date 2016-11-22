#include "InputManager.h"

namespace SushiEngine
{
	/* ---- STATIC ---- */
	InputManager* InputManager::sInstance = nullptr;

	void InputManager::KeyCallback(GLFWwindow* pGlfwWindow, int key, int scancode, int action, int mods)
	{
		//Update state
		sInstance->mKeyData[key] = action;

		//Print to console
		if (action == GLFW_PRESS)
		{
			Debug::Print(string("Keypressed: ") + (char(key)));
		}
		else if (action == GLFW_RELEASE)
		{
			Debug::Print(string("Released: ") + (char(key)));
		}
		else if (action == GLFW_REPEAT)
		{
			Debug::Print(string("Repeated: ") + (char(key)));
		}
	}

	void InputManager::ClickCallback(GLFWwindow* pGlfwWindow, int button, int action, int mods)
	{
		Debug::Print("Click.");
	}

	void InputManager::MouseMoveCallback(GLFWwindow * pGlfwWindow, double pMouseX, double pMouseY)
	{
		sInstance->mMouseX = pMouseX;
		sInstance->mMouseY = pMouseY;
	}
	/* ---- End of STATIC ---- */
	/* ---- INSTANCE ---- */
	InputManager::InputManager()
	{
		Debug::LogConstructor("InputManager", __FILENAME__, __LINE__);
		if (sInstance == nullptr)
		{
			sInstance = this;
		}
		else
		{
			Debug::Log(EMessageType::S_WARNING, "\tInputManager() - More than one InputManager has been created.", __FILENAME__, __LINE__);
		}
	}

	InputManager::~InputManager()
	{
		Debug::LogDeconstructor("InputManager", __FILENAME__, __LINE__);
	}

	bool InputManager::isKeyDown(int pKey)
	{
		return mKeyData[pKey] == GLFW_PRESS || mKeyData[pKey] == GLFW_REPEAT;
	}

	void InputManager::getMousePosition(double* pXreference, double* pYReference)
	{
		*pXreference = mMouseX;
		*pYReference = mMouseY;
	}
	/* ---- End of INSTANCE ---- */
}