//VCommander - Maintains the Vulkan command pool, buffers, and synchronization objects.

//TODO: Currently, number of buffers is arbitrarily set to 2.
#ifndef V_COMMANDER_H
#define V_COMMANDER_H

#include "vulkan\vulkan.h"
#include "VHelper.h"

namespace SushiEngine {
	class VCommander
	{
	public:
		VCommander(uint32_t queueFamilyIndex, uint32_t queueCount, VkDevice);
		~VCommander();

		//
		static const int BUFFER_COUNT;

		//Vulkan objects
		VkCommandPool commandPool;
		VkCommandBuffer * commandBuffers;
		VkSwapchainKHR swapchain;

	private:
		//Private data
		uint32_t queueFamilyIndex;
		uint32_t queueCount;
		VkDevice device;

		//Creational methods
		void createSwapchain();
		void createCommandPool();
		void createCommandBuffers();
		void recordCommandBuffers();
		void submitCommandBuffers();

		//Helper methods
		void getQueue(VkQueue* queueHandle, uint32_t queueIndex);

	};
}
#endif
