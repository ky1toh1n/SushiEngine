//VInitializer - Initializes the Vulkan context.
//It creates the Vulkan objects that are made only once per program lifetime.
//This includes VkInstance, VkPhysicalDevice, VkDevice
#ifndef V_INITIALIZER_H
#define V_INITIALIZER_H
#include "vulkan\vulkan.h"
#include "VHelper.h"
#include "Debug.h"

namespace SushiEngine {
	class VRenderer;
	class VInitializer
	{
	public:
		VInitializer();
		~VInitializer();

		//Vulkan Objects
		VkInstance instance;
		VkPhysicalDevice physicalDevice;
		VkDevice device;

	private:
		//Creational methods
		void CreateVulkanInstance();
		void SelectPhysicalDevice();
		void CreateLogicalDevice();
	};
}
#endif
