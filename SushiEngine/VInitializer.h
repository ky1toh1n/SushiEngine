//VInitializer - Initializes the Vulkan context.
//It creates the Vulkan objects that are made only once per program lifetime.
//This includes VkInstance, VkPhysicalDevice, VkDevice

//TODO: Right now, Queue family selection is hard coded.
//We need to learn more about handling different GPUs and how we want to use the queues.
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

		//Selected queue family & accessor
		uint32_t queueFamilyIndex;
		uint32_t queueCount;

		void getQueue(VkQueue* queueHandle, uint32_t queueIndex);

	private:
		//Creational methods
		void CreateVulkanInstance();
		void SelectPhysicalDevice();
		void CreateLogicalDevice();
	};
}
#endif
