#include "VCommander.h"

namespace SushiEngine {
	//Initialize buffer count
	const int VCommander::BUFFER_COUNT = 2;

	VCommander::VCommander(uint32_t queueFamilyIndex, uint32_t queueCount,
		VkDevice device) : queueFamilyIndex(queueFamilyIndex),
		queueCount(queueCount), device(device)
	{
		Debug::Log(EMessageType::S_INFO, "\t\tCommander() ", __FILENAME__, __LINE__);
		createCommandPool();
		createCommandBuffers();
		recordCommandBuffers();
		submitCommandBuffers();
	}


	VCommander::~VCommander()
	{
		Debug::Log(EMessageType::S_INFO, "\t\t~Commander() ", __FILENAME__, __LINE__);
		vkFreeCommandBuffers(device, commandPool, BUFFER_COUNT, commandBuffers);
		vkDestroyCommandPool(device, commandPool, NULL);
	}

	void VCommander::createSwapchain() {

	}

	void VCommander::createCommandPool()
	{
		VkCommandPoolCreateInfo createInfo{
			//sType
			VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
			//pNext, unused
			NULL,
			//flags for pool&buffer behavior. 0 for now.
			0,
			//queueFamilyIndex
			queueFamilyIndex
		};
		
		HANDLE_VK_RESULT(vkCreateCommandPool(device, &createInfo, NULL, &commandPool));
	}

	void VCommander::createCommandBuffers() {
		VkCommandBufferAllocateInfo allocateInfo{
			//sType
			VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
			//pNext
			NULL,
			//commandPool
			commandPool,
			//level (primary vs. secondary)
			VK_COMMAND_BUFFER_LEVEL_PRIMARY,
			//buffer count
			BUFFER_COUNT
		};

		commandBuffers = new VkCommandBuffer[BUFFER_COUNT];
		HANDLE_VK_RESULT(vkAllocateCommandBuffers(device, &allocateInfo, commandBuffers));
	}

	void VCommander::recordCommandBuffers() {
		VkCommandBufferBeginInfo beginInfo{
			//sType
			VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
			//pNext
			NULL,
			//flags 
			VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT, //()
			//pInheritanceInfo (used only for secondary buffers)
			VK_NULL_HANDLE
		};

		///Record for each buffer!!
		for (int i = 0; i < BUFFER_COUNT; i++)
		{
			HANDLE_VK_RESULT(vkBeginCommandBuffer(commandBuffers[i], &beginInfo));

			//needs a render pass & graphics pipeline
			
			HANDLE_VK_RESULT(vkEndCommandBuffer(commandBuffers[i]));
		}
	}


	void VCommander::getQueue(VkQueue * queueHandle, uint32_t queueIndex) {

		if (queueIndex >= queueCount) {
			Debug::Log(EMessageType::S_FATAL_ERROR, "\t\tVCommander()/getQueue ", __FILENAME__, __LINE__);
			throw "This queue index: " + std::to_string(queueIndex) + " does not exist on this queue family.";
		}

		vkGetDeviceQueue(device, queueFamilyIndex, queueIndex, queueHandle);
	}


	void VCommander::submitCommandBuffers() {
		///Select a queue to submit to
		VkQueue queue;
		getQueue(&queue, 0);


		VkSubmitInfo submitInfo;
		//submitInfo.

		//vkQueueSubmit(queue, 
	}
}
