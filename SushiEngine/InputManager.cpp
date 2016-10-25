#include "InputManager.h"


namespace SushiEngine {
	/// See the header file reguarding unique_ptr
	std::unique_ptr<InputManager> InputManager::instance(nullptr);

	InputManager::InputManager()
	{

	}

	InputManager::~InputManager()
	{

	}

	InputManager* InputManager::GetInstance() {
		if (instance == nullptr) {
			instance.reset(new InputManager());
		}
		return instance.get();
	}

	void InputManager::KeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
		GetInstance()->keyData[key] = action;
		//
		//if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		//	Debug::Print("Pressed W");
		//}
		if (key == GLFW_KEY_W && action == GLFW_PRESS) {
			Debug::Print("pressed key W");
		} else if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
			Debug::Print("released key W");
		} else if (key == GLFW_KEY_W && action == GLFW_REPEAT) {
			Debug::Print("repeated key W");
		}
	}

	void InputManager::ClickCallback(GLFWwindow* glfwWindow, int button, int action, int mods) {
		//
		Debug::Print("click!");
	}
}