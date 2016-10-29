#include "VRenderer.h"

namespace SushiEngine {

	/************** Vulkan Renderer Class ****************/

	VRenderer::VRenderer(GLFWwindow* window) : _window(window)
	{
		Initialize();
		Debug::Log(EMessageType::S_INFO, "Vulkan Renderer Initialized.", __FILENAME__, __LINE__);
	}

	VRenderer::~VRenderer()
	{
		Debug::Log(EMessageType::S_INFO, "Vulkan Renderer Destroyed.", __FILENAME__, __LINE__);
	}

	/* Member Functions */
	//Initialize vulkan objects one by one
	void VRenderer::Initialize()
	{
		instance = VInitializer::createInstance();
	    callback = VInitializer::setupDebugCallback(instance);
		surface = VInitializer::createSurface(instance, _window);
		physicalDevice = VInitializer::pickPhysicalDevice(instance, surface);
		device = VInitializer::createLogicalDevice(physicalDevice, graphicsQueue, presentQueue, surface);
		createSwapChain();
		createImageViews();
		renderPass = VGraphicsPipeline::createRenderPass(*device, swapChainImageFormat);
		graphicsPipeline = VGraphicsPipeline::createGraphicsPipeline(*device, swapChainExtent, *renderPass);
	}

	/* Presentation: Window Surface + Swap Chain + Image Views  */
	void VRenderer::createSwapChain()
	{
		swapChain = new VDeleter<VkSwapchainKHR>{ *device, vkDestroySwapchainKHR };

		SwapChainSupportDetails swapChainSupport = VInitializer::querySwapChainSupport(physicalDevice, surface);

		VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
		VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
		VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
			imageCount = swapChainSupport.capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = *surface;
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		QueueFamilyIndices indices = VInitializer::findQueueFamilies(physicalDevice, surface);
		uint32_t queueFamilyIndices[] = { (uint32_t)indices.graphicsFamily, (uint32_t)indices.presentFamily };

		if (indices.graphicsFamily != indices.presentFamily) {
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else {
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0; // Optional
			createInfo.pQueueFamilyIndices = nullptr; // Optional
		}

		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;

		if (vkCreateSwapchainKHR(*device, &createInfo, nullptr, swapChain->replace()) != VK_SUCCESS) {
			 throw std::runtime_error("failed to create swap chain!");
		}

		// retrieve swap chain images
		
		//vkGetSwapchainImagesKHR(*device, *swapChain, &imageCount, nullptr);
		//swapChainImages.resize(imageCount);
		//vkGetSwapchainImagesKHR(*device, *swapChain, &imageCount, swapChainImages.data());

		swapChainImageFormat = surfaceFormat.format;
		swapChainExtent = extent;
		
	}

	void VRenderer::createImageViews()
	{
		swapChainImageViews.resize(swapChainImages.size(), VDeleter<VkImageView>{*device, vkDestroyImageView});

		for (uint32_t i = 0; i < swapChainImages.size(); i++) {
			VkImageViewCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image = swapChainImages[i];
			createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			createInfo.format = swapChainImageFormat;
			createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;

			if (vkCreateImageView(*device, &createInfo, nullptr, swapChainImageViews[i].replace()) != VK_SUCCESS) {
				Debug::Log(EMessageType::S_ERROR, "failed to create image views!", __FILENAME__, __LINE__);
				throw std::runtime_error("failed to create image views!");
			}
		}
	}

	/*Helper Functions*/
	VkSurfaceFormatKHR VRenderer::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) {
			return{ VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
		}

		for (const auto& availableFormat : availableFormats) {
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
				return availableFormat;
			}
		}

		return availableFormats[0];
	}

	VkPresentModeKHR VRenderer::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes)
	{
		for (const auto& availablePresentMode : availablePresentModes) {
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
				return availablePresentMode;
			}
		}

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D VRenderer::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
	{
		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
			return capabilities.currentExtent;
		}
		else {
			glfwGetWindowSize(_window, windowWidth, windowHeight);
			VkExtent2D actualExtent = { *windowWidth, *windowHeight };

			actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
			actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

			return actualExtent;
		}
	}

}