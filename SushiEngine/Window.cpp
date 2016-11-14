#include "Window.h"

namespace SushiEngine 
{
	//Creates a window with specificed parameters
	Window::Window(const char* title, const int width, const int height)
	{
		Debug::Log(EMessageType::S_INFO, "\tWindow(char*,int,int)", __FILENAME__, __LINE__);
		Initialize(title, width, height);
	}

	//Handles termination of the GLFW library.
	Window::~Window() 
	{
		Debug::Log(EMessageType::S_INFO, "\t~Window()", __FILENAME__, __LINE__);
		glfwTerminate();
	}

	//Attempts to create a GLFW window and set its title and screen dimensions.
	bool Window::Initialize(const char* title, const int width, const int height)
	{
		Debug::Log(EMessageType::S_INFO, "\tWindow::Initialize()", __FILENAME__, __LINE__);
		isInitialized = false;

		if (!glfwInit()) 
		{
			Debug::Log(EMessageType::S_FATAL_ERROR, "\tGLFW cannot be initialized!", __FILENAME__, __LINE__);
			return false;
		}

		// Unless you will be using OpenGL or OpenGL ES with the same window as Vulkan, there is no need to create a context.
		// You can disable context creation with the GLFW_CLIENT_API hint.

		//glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		// glfwWindow = glfwCreateWindow(640, 480, "My Title", glfwGetPrimaryMonitor(), NULL); // Reserved for multiple viewports or fullscreen handling
		glfwWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if (!glfwWindow)
		{
			Debug::Log(EMessageType::S_FATAL_ERROR, "\tWindow or OpenGL context creation failed", __FILENAME__, __LINE__);
			return false;
		}

		glfwMakeContextCurrent(glfwWindow);
		// indicate how many frames to wait until swapping the buffers, commonly known as vsync
		glfwSwapInterval(1);

		isInitialized = true;
		
		return true;
	}

	//Terminates the GLFW Window.
	void Window::Destroy() 
	{
		Debug::Log(EMessageType::S_INFO, "\tWindow->Destroy()", __FILENAME__, __LINE__);
		/*
		When a window is no longer needed, destroy it with glfwDestroyWindow.

		Window destruction always succeeds. Before the actual destruction, all callbacks are removed so no further events will be delivered for the window.
		All windows remaining when glfwTerminate is called are destroyed as well.
		*/
		glfwDestroyWindow(glfwWindow);
	}

	//Returns a pointer to the GLFWwindow.
	GLFWwindow* Window::GetWindowHandle()
	{
		return glfwWindow;
	}

	//Sets the window title.
	void Window::SetTitle(const char* title) 
	{
		glfwSetWindowTitle(glfwWindow, title);
	}
	
	//TODO: [DOES NOT WORK]
	void Window::SetSize(const int width, const int height) 
	{
		glfwSetWindowSize(glfwWindow, width, height);
		// glfwSetWindowAspectRatio(glfwWindow, width, height);
		// glfwSetWindowSizeLimits(glfwWindow, width, height, GLFW_DONT_CARE, GLFW_DONT_CARE);
	}

	void Window::GetSize(int*width, int*height) 
	{
		glfwGetWindowSize(glfwWindow, width, height);
	}

	//TODO: [MISSING IMPLEMENTATION]
	//
	void Window::Clear() 
	{

	}
}