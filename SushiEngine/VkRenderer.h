#ifndef VK_RENDERER_H
#define VK_RENDERER_H
#include <chrono>
#include "vulkan/vulkan.h"
#include "Debug.h"
#include "GLFW\glfw3.h"
#include "VDeleter.h"
#include <vector>

namespace SushiEngine {
	class VkRenderer
	{
	public:
		VkRenderer();
		~VkRenderer();

	private:
		//Helper Functions
		bool checkValidationLayerSupport();

		//Fields
		VDeleter<VkInstance> instance{ vkDestroyInstance };

		
		//Core creational functions
		void createInstance();

	};


}
#endif