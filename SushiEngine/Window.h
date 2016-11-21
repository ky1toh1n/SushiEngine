/*Window - Represents the Window instance. It uses GLFW.*/
#ifndef WINDOW_H
#define WINDOW_H
/* Third Party */
#include <GL\glew.h>
#include <GLFW\glfw3.h>
/* SushiEngine */
#include "Debug.h"
#include "Macros.h"
/* ---- */
namespace SushiEngine
{
	class SceneContext;
	class Window
	{
	public:
		/* Constructor */
		NO_COPY_CONSTRUCTORS(Window)

		/* Instance Functions */
		GLFWwindow* GetWindowHandle();
		void SetTitle(const char* title);
		void SetSize(const int width, const int height);
		void GetSize(int *, int*);
		void Clear();

	private:
		/* Constructor */
		//Only the SceneContext may instantiate this class.
		friend class SceneContext;
		explicit Window(const char* title, const int width, const int height);
		~Window();

		/* Instance fields */
		GLFWwindow* glfwWindow;
		bool isInitialized;

		/* Instance methods */
		bool Initialize(const char* title = "No Data", const int width = 640, const int height = 480);
		void Destroy();
	};
}
#endif