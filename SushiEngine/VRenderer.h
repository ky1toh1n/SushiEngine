//VRenderer - Responsible for rendering 3D scenes through Vulkan.
//It uses helper classes in order to instantiate necessary Vulkan objects.
#ifndef VRENDERER_H
#define VRENDERER_H
#include "vulkan/vulkan.h"
#include "GLFW\glfw3.h"
#include "Debug.h"
#include "VInitializer.h"
#include "VCommander.h"

namespace SushiEngine {
	class GameSceneManager;

	// Vulkan Renderer Class
	class VRenderer
	{
	public:
		VRenderer(GLFWwindow* window);
		~VRenderer();

	private:
		/* Fields */
		GLFWwindow* _window;
		int* windowWidth;
		int* windowHeight;

		/*Vulkan objects*/
		VInitializer * initializer;
		VCommander * commander;
	};
}
#endif