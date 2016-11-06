//VCommander - Maintains the Vulkan command pool, buffers, and synchronization objects.

//TODO: Currently, number of buffers is arbitrarily set to 2.
#ifndef V_COMMANDER_H
#define V_COMMANDER_H

#include "vulkan\vulkan.h"
#include "VHelper.h"
#include "VInitializer.h"

namespace SushiEngine {
	class VCommander
	{
	public:
		VCommander(VInitializer * initializer);
		~VCommander();

		//
		static const int BUFFER_COUNT;

		//Vulkan objects
		VkCommandPool commandPool;
		VkCommandBuffer * commandBuffers;
		VkSwapchainKHR swapchain;

	private:
		//Private data
		VInitializer * initializer;
		VkSemaphore imageAvailableSemaphore;
		VkSemaphore renderingFinishedSemaphore;

		//Core methods
		void createSemaphores();
		void createSwapchain();
		void createCommandPool();
		void createCommandBuffers();
		void recordCommandBuffers();
		void submitCommandBuffers();

		//Helper methods
		void getQueue(VkQueue* queueHandle, uint32_t queueIndex);
		VkSurfaceFormatKHR getSurfaceFormat();
		VkExtent2D getSwapchainExtent(VkSurfaceCapabilitiesKHR);
		VkImageUsageFlags getImageUsageFlags(VkSurfaceCapabilitiesKHR);
		VkSurfaceTransformFlagBitsKHR getPretransformations(VkSurfaceCapabilitiesKHR);
		VkPresentModeKHR getPresentMode(VkSurfaceCapabilitiesKHR);
	};
}
#endif
