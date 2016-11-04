//VRenderer - Responsible for rendering 3D scenes through Vulkan.
//It uses helper classes in order to instantiate necessary Vulkan objects.
#ifndef VRENDERER_H
#define VRENDERER_H
#include "vulkan/vulkan.h"
#include "Debug.h"
#include "GLFW\glfw3.h"
#include "VInitializer.h"

//Use this with all of Vulkan's creational methods that return a VkResult

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
		VInitializer initializer;
	};
}
#endif