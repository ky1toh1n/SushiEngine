#include "Window.h"

namespace SushiEngine 
{

	Window::Window() { }

	Window::~Window() { 
		Shutdown();
	}

	bool Window::Initialize() {
		Debug::Log(EMessageType::INFO, "	Window->Initialize()", __FILENAME__, __LINE__);
		isInitialized = false;

		if (!glfwInit()) {
			Debug::Log(EMessageType::FATAL_ERROR, "GLFW cannot be initialized!", __FILENAME__, __LINE__);
			return false;
		}

		// Unless you will be using OpenGL or OpenGL ES with the same window as Vulkan, there is no need to create a context.
		// You can disable context creation with the GLFW_CLIENT_API hint.

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);


		// glfwWindow = glfwCreateWindow(640, 480, "My Title", glfwGetPrimaryMonitor(), NULL); // Reserved for multiple viewports or fullscreen handling
		glfwWindow = glfwCreateWindow(640, 480, "No Data", NULL, NULL);
		if (!glfwWindow) {
			Debug::Log(EMessageType::FATAL_ERROR, "Unable to Create GLFW Window!", __FILENAME__, __LINE__);
			return false;
		}

		//glfwMakeContextCurrent(glfwWindow); Context not needed when involving vulkan i think

		isInitialized = true;
		return true;
	}

	void Window::Shutdown() {
		Debug::Log(EMessageType::INFO, "	Window->ShutDown()", __FILENAME__, __LINE__);
		/*
		When a window is no longer needed, destroy it with glfwDestroyWindow.

		Window destruction always succeeds. Before the actual destruction, all callbacks are removed so no further events will be delivered for the window.
		All windows remaining when glfwTerminate is called are destroyed as well.
		*/
		// glfwDestroyWindow(glfwWindow);

	}

	GLFWwindow* Window::GetWindowHandle() {
		return glfwWindow;
	}

	void Window::SetTitle(const char* title) {
		glfwSetWindowTitle(glfwWindow, title);
	}
	
	void Window::SetSize(const int width, const int height) {
		glfwSetWindowSize(glfwWindow, width, height);
		// glfwSetWindowAspectRatio(glfwWindow, width, height);
		// glfwSetWindowSizeLimits(glfwWindow, width, height, GLFW_DONT_CARE, GLFW_DONT_CARE);
	}

	void Window::Clear() {

	}
}