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
	SceneContext::SceneContext(const char * pTitle, const int pWidth, const int pHeight)
	{
		window = new Window(pTitle, pWidth, pHeight);
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
		glfwSetCursorEnterCallback(glfwHandle, InputManager::WindowEnterCallback);
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
