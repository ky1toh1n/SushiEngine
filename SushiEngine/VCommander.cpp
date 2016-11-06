#include "VCommander.h"

namespace SushiEngine {
	//Initialize buffer count
	const int VCommander::BUFFER_COUNT = 2;

	VCommander::VCommander(VInitializer * initializer) : initializer(initializer)
	{
		Debug::Log(EMessageType::S_INFO, "\t\tCommander() ", __FILENAME__, __LINE__);
		createSemaphores();
		createSwapchain();
		createCommandPool();
		createCommandBuffers();
		recordCommandBuffers();
		submitCommandBuffers();
	}


	VCommander::~VCommander()
	{
		Debug::Log(EMessageType::S_INFO, "\t\t~Commander() ", __FILENAME__, __LINE__);
		vkFreeCommandBuffers(initializer->device, commandPool, BUFFER_COUNT, commandBuffers);
		vkDestroyCommandPool(initializer->device, commandPool, nullptr);
		vkDestroySwapchainKHR(initializer->device, swapchain, nullptr);
	}

	void VCommander::createSemaphores() {
		VkSemaphoreCreateInfo createInfo;
		createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		createInfo.pNext = nullptr;
		createInfo.flags = 0;

		HANDLE_VK_RESULT(vkCreateSemaphore(initializer->device, &createInfo, nullptr, &imageAvailableSemaphore));
		HANDLE_VK_RESULT(vkCreateSemaphore(initializer->device, &createInfo, nullptr, &renderingFinishedSemaphore));
	}

	//Selects the ideal surface format for the swap chain images
	VkSurfaceFormatKHR VCommander::getSurfaceFormat() {
		///get surface formats
		uint32_t surfaceFormatsCount = 0;
		HANDLE_VK_RESULT(vkGetPhysicalDeviceSurfaceFormatsKHR(initializer->physicalDevice, initializer->surface, &surfaceFormatsCount, nullptr));
		VkSurfaceFormatKHR * surfaceFormats = new VkSurfaceFormatKHR[surfaceFormatsCount];
		HANDLE_VK_RESULT(vkGetPhysicalDeviceSurfaceFormatsKHR(initializer->physicalDevice, initializer->surface, &surfaceFormatsCount, surfaceFormats));

		///selecting surface format
		//If there's only one undefined surface; it means any can be returned
		if ((surfaceFormatsCount == 1)
			&& (surfaceFormats[0].format == VK_FORMAT_UNDEFINED))
		{
			return{ VK_FORMAT_R8G8B8A8_SNORM, VK_COLORSPACE_SRGB_NONLINEAR_KHR };
		}

		//otherwise, let's search for the ideal format
		for (int i = 0; i < surfaceFormatsCount; i++)
		{
			if (surfaceFormats[i].format == VK_FORMAT_R8G8B8A8_UNORM) {
				return surfaceFormats[i];
			}
		}

		//if we can't find it, we return the first one.
		return surfaceFormats[0];

		///QUESTION: Should the surfaceFormat handle be deallocated?
	}

	VkExtent2D VCommander::getSwapchainExtent(VkSurfaceCapabilitiesKHR surfaceCapabilities)
	{
		// If the extent is {-1, -1}, we have to define the size ourselves
		// while making sure it's between the min and max imageExtent.
		if (surfaceCapabilities.currentExtent.width == -1) {
			//Set the default or ideal size
			VkExtent2D swapchainExtent = { 640, 480 };

			//Clamp through the width and height of the min and max image extent.
			if (swapchainExtent.width <= surfaceCapabilities.minImageExtent.width) {
				swapchainExtent.width = surfaceCapabilities.minImageExtent.width;
			}

			if (swapchainExtent.height <= surfaceCapabilities.minImageExtent.height) {
				swapchainExtent.height = surfaceCapabilities.minImageExtent.height;
			}
			if (swapchainExtent.width <= surfaceCapabilities.maxImageExtent.width) {
				swapchainExtent.width = surfaceCapabilities.maxImageExtent.width;
			}
			if (swapchainExtent.height <= surfaceCapabilities.maxImageExtent.height) {
				swapchainExtent.height = surfaceCapabilities.maxImageExtent.height;
			}

			return swapchainExtent;
		}

		//Otherwise, we just use the current extent.
		return surfaceCapabilities.currentExtent;
	}


	VkImageUsageFlags VCommander::getImageUsageFlags(VkSurfaceCapabilitiesKHR surfaceCapabilities) {
		// Color attachment flag must always be supported
		// We can define other usage flags but we always need to check if they are supported
		if (surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_DST_BIT) {
			return VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
		}
		std::cout << "VK_IMAGE_USAGE_TRANSFER_DST image usage is not supported by the swap chain!" << std::endl
			<< "Supported swap chain's image usages include:" << std::endl
			<< (surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_SRC_BIT ? "    VK_IMAGE_USAGE_TRANSFER_SRC\n" : "")
			<< (surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_DST_BIT ? "    VK_IMAGE_USAGE_TRANSFER_DST\n" : "")
			<< (surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_SAMPLED_BIT ? "    VK_IMAGE_USAGE_SAMPLED\n" : "")
			<< (surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_STORAGE_BIT ? "    VK_IMAGE_USAGE_STORAGE\n" : "")
			<< (surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT ? "    VK_IMAGE_USAGE_COLOR_ATTACHMENT\n" : "")
			<< (surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT ? "    VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT\n" : "")
			<< (surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT ? "    VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT\n" : "")
			<< (surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT ? "    VK_IMAGE_USAGE_INPUT_ATTACHMENT" : "")
			<< std::endl;
		return static_cast<VkImageUsageFlags>(-1);
	}


	VkSurfaceTransformFlagBitsKHR VCommander::getPretransformations(VkSurfaceCapabilitiesKHR surfaceCapabilities) {
		//Try to use identity/no transformation; otherwise use the current one.
		if (surfaceCapabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR) {
			return VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
		}
		else {
			return surfaceCapabilities.currentTransform;
		}
	}

	VkPresentModeKHR VCommander::getPresentMode(VkSurfaceCapabilitiesKHR surfaceCapabilities) {
		///get present modes
		uint32_t presentModesCount = 0;
		HANDLE_VK_RESULT(vkGetPhysicalDeviceSurfacePresentModesKHR(initializer->physicalDevice, initializer->surface, &presentModesCount, nullptr));
		VkPresentModeKHR * presentModes = new VkPresentModeKHR[presentModesCount];
		HANDLE_VK_RESULT(vkGetPhysicalDeviceSurfacePresentModesKHR(initializer->physicalDevice, initializer->surface, &presentModesCount, presentModes));

		///select a present mode
		// FIFO present mode is always available
		// MAILBOX is the lowest latency V-Sync enabled mode (something like triple-buffering) so use it if available
		for (int i = 0; i < presentModesCount; i++) {
			if (presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR) {
				return presentModes[i];
			}
		}
		for (int i = 0; i < presentModesCount; i++) {
			if (presentModes[i] == VK_PRESENT_MODE_FIFO_KHR) {
				return presentModes[i];
			}
		}
		std::cout << "FIFO present mode is not supported by the swap chain!" << std::endl;
		return static_cast<VkPresentModeKHR>(-1);
	}

	void VCommander::createSwapchain() {
		///Gathering and validating all the info needed to make a swap chain
		//get surface capabilities
		VkSurfaceCapabilitiesKHR surfaceCapabilities;
		HANDLE_VK_RESULT(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(initializer->physicalDevice, initializer->surface, &surfaceCapabilities));

		//get surface format
		VkSurfaceFormatKHR surfaceFormat = getSurfaceFormat();

		//select an image count
		uint32_t imageCount = surfaceCapabilities.minImageCount + 1;
		if ((surfaceCapabilities.maxImageCount > 0)
			&& (imageCount > surfaceCapabilities.maxImageCount)) {
			imageCount = surfaceCapabilities.maxImageCount;
		}

		//selecting settings that need surfaceCapabilities
		VkExtent2D swapchainExtent = getSwapchainExtent(surfaceCapabilities);
		VkImageUsageFlags imageUsageFlags = getImageUsageFlags(surfaceCapabilities);
		VkSurfaceTransformFlagBitsKHR transform = getPretransformations(surfaceCapabilities);
		VkPresentModeKHR presentMode = getPresentMode(surfaceCapabilities);

		///Putting the actual swap chain together
		VkSwapchainCreateInfoKHR createInfo;
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.pNext = NULL;
		createInfo.flags = 0;
		createInfo.surface = initializer->surface;
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = swapchainExtent;
		createInfo.imageArrayLayers = 1; //Always 1 for non-stereoscopic apps
		createInfo.imageUsage = imageUsageFlags;
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		//Queue family fields are optional on EXCLUSIVE
		createInfo.queueFamilyIndexCount = 0;
		createInfo.pQueueFamilyIndices = nullptr;
		createInfo.preTransform = transform;
		createInfo.presentMode = presentMode;
		//yolo
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;

		//TODO: Handle oldswapchain, and learn more about the swapchain settings.

		vkCreateSwapchainKHR(initializer->device, &createInfo, nullptr, &swapchain);
	}

	void VCommander::createCommandPool()
	{
		VkCommandPoolCreateInfo createInfo{
			//sType
			VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
			//pNext, unused
			nullptr,
			//flags for pool&buffer behavior. 0 for now.
			0,
			//queueFamilyIndex
			initializer->queueFamilyIndex
		};

		HANDLE_VK_RESULT(vkCreateCommandPool(initializer->device, &createInfo, nullptr, &commandPool));
	}

	void VCommander::createCommandBuffers() {
		VkCommandBufferAllocateInfo allocateInfo{
			//sType
			VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
			//pNext
			nullptr,
			//commandPool
			commandPool,
			//level (primary vs. secondary)
			VK_COMMAND_BUFFER_LEVEL_PRIMARY,
			//buffer count
			BUFFER_COUNT
		};

		commandBuffers = new VkCommandBuffer[BUFFER_COUNT];
		HANDLE_VK_RESULT(vkAllocateCommandBuffers(initializer->device, &allocateInfo, commandBuffers));
	}

	void VCommander::recordCommandBuffers() {
		VkCommandBufferBeginInfo beginInfo{
			//sType
			VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
			//pNext
			nullptr,
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

		if (queueIndex >= initializer->queueCount) {
			Debug::Log(EMessageType::S_FATAL_ERROR, "\t\tVCommander()/getQueue ", __FILENAME__, __LINE__);
			throw "This queue index: " + std::to_string(queueIndex) + " does not exist on this queue family.";
		}

		vkGetDeviceQueue(initializer->device, initializer->queueFamilyIndex, queueIndex, queueHandle);
	}


	void VCommander::submitCommandBuffers() {
		///Select a queue to submit to
		VkQueue queue;
		getQueue(&queue, 0);

		VkSubmitInfo submitInfo;
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.pNext = nullptr;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = commandBuffers;
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = &imageAvailableSemaphore;
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = &renderingFinishedSemaphore;
		//yolo again
		VkPipelineStageFlags wait_dst_stage_mask = VK_PIPELINE_STAGE_TRANSFER_BIT;
		submitInfo.pWaitDstStageMask = &wait_dst_stage_mask;

		HANDLE_VK_RESULT(vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE));


		///presenting
		//ihave no idea what im doing anymore.. 
		VkPresentInfoKHR presentInfo = {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = &renderingFinishedSemaphore;

		VkSwapchainKHR swapChains[] = { swapchain };
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;

		presentInfo.pImageIndices = 0;

		getQueue(&queue, 1);
		vkQueuePresentKHR(queue, &presentInfo);

	}
}
