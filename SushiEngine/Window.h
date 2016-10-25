//Window - Represents the Window instance. It uses GLFW.
#ifndef WINDOW_H
#define WINDOW_H

#define GLFW_INCLUDE_VULKAN
//#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW\glfw3.h>
//#include "GLFW\glfw3native.h"
#include "Debug.h"

namespace SushiEngine {
	//Avoids circular dependency
	class GameSceneManager;

	class Window {
		//A window may only be instantiated in GameSceneManager
		friend class GameSceneManager;
	private:
		//Private constructor
		Window(const char* title, const int width, const int height);
		~Window();

		//Private fields
		GLFWwindow* glfwWindow;
		bool isInitialized;

		//Private functions
		bool Initialize(const char* title = "Vulkan Application", const int width = 640, const int height = 480);
		void Destroy();
	public:
		/// C11 precautions delete these non-needed default constructors and operators
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator = (const Window&) = delete;
		Window& operator = (Window&&) = delete;

		//Public functions
		GLFWwindow* GetWindowHandle();
		void SetTitle(const char* title);
		void SetSize(const int width, const int height);
		void Clear();
	};
}
#endif