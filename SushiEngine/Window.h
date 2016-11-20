//Window - Represents the Window instance. It uses GLFW.
#ifndef WINDOW_H
#define WINDOW_H

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "Debug.h"

namespace SushiEngine
{
	class SceneContext;
	class Window
	{
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
		void GetSize(int *, int*);
		void Clear();

	private:
		//Private constructor
		friend class SceneContext;
		explicit Window(const char* title, const int width, const int height);
		~Window();

		//Private fields
		GLFWwindow* glfwWindow;
		bool isInitialized;

		//Private functions
		bool Initialize(const char* title = "No Data", const int width = 640, const int height = 480);
		void Destroy();
	};
}
#endif