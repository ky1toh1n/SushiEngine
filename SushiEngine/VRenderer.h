//VRenderer - Responsible for rendering 3D scenes through Vulkan.
//It uses helper classes in order to instantiate necessary Vulkan objects.
#ifndef VRENDERER_H
#define VRENDERER_H
#include "vulkan/vulkan.h"
#include "Debug.h"
#include "GLFW\glfw3.h"

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
		VkInstance instance;
		VkPhysicalDevice physicalDevice;
		VkDevice device;

		//Member function
		void Initialize();
		void SelectPhysicalDevice();
		void CreateLogicalDevice();
	};
}
#endif