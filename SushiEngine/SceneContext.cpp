#include "SceneContext.h"

namespace SushiEngine
{
	/* ---- GLFW Callback Functions --- */
	static void CloseWindowCallback(GLFWwindow* pGlfwWindow)
	{
		glfwSetWindowShouldClose(pGlfwWindow, GLFW_TRUE);
	}

	static void ResizeWindowCallback(GLFWwindow* pGlfwWindow, int pWidth, int pHeight)
	{
		glViewport(0, 0, pWidth, pHeight);
	}
	/* ---- End of GLFW Callback ---- *

	/* Constructor */
	SceneContext::SceneContext(const char * title, const int width, const int height)
	{
		window = new Window(title, width, height);
		renderer = new OpenGLRenderer(window);
		input = new InputManager();

		// Initialize GLFW Window Callbacks
		GLFWwindow* glfwHandle = window->GetWindowHandle();
		glfwSetWindowUserPointer(glfwHandle, this);
		glfwSetWindowCloseCallback(glfwHandle, CloseWindowCallback);
		glfwSetWindowSizeCallback(glfwHandle, ResizeWindowCallback);

		// Initialize GLFW Input Callbacks
		glfwSetKeyCallback(glfwHandle, InputManager::KeyCallback);
		//glfwSetCharCallback(glfwHandle, InputManager::CharCallback);
		glfwSetMouseButtonCallback(glfwHandle, InputManager::ClickCallback);
		glfwSetCursorPosCallback(glfwHandle, InputManager::MouseMoveCallback);
	}

	SceneContext::~SceneContext()
	{
		delete(renderer);
		delete(window);
		delete(input);
	}

	void SceneContext::destroy()
	{
		window->Destroy();
	}

}
