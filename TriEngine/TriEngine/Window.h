#ifndef WINDOW_H
#define WINDOW_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW\glfw3.h>

#include "Debug.h"

namespace TriEngine {
	class Window {
	public:
		Window();
		~Window();

		/// C11 precautions delete these non-needed default constructors and operators
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator = (const Window&) = delete;
		Window& operator = (Window&&) = delete;

		bool Initialize();
		void Shutdown();

		GLFWwindow* GetWindowHandle();

		void SetTitle(const char* title);
		void SetSize(const int width, const int height);

		void Clear();
		
	private:
		GLFWwindow* glfwWindow;

		bool isInitialized;


	};
}

#endif