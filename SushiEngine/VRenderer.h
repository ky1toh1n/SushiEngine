//VRenderer - Responsible for rendering 3D scenes through Vulkan.
//It uses helper classes in order to instantiate necessary Vulkan objects.
#ifndef VRENDERER_H
#define VRENDERER_H
#include <chrono>
#include "vulkan/vulkan.h"
#include "Debug.h"
#include "GLFW\glfw3.h"
#include "VDeleter.h"
#include "VStructs.h"
#include <vector>
#include <algorithm>
#include "VInitializer.h"
#include "VGraphicsPipeline.h"

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

		/* Vulkan objects */
		//------
		VDeleter<VkInstance> * instance; // Vulkan Instance		
		VDeleter<VkDebugReportCallbackEXT> * callback; // Debug Callback		
		VDeleter<VkSurfaceKHR> * surface; // Surface
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE; // Physical Graphics Device		
		VDeleter<VkDevice> * device; // Logical Graphics Device
		VkQueue graphicsQueue; // Graphics Queue Handle
		VkQueue presentQueue; // Presentation Queue

		//-----
		VDeleter<VkSwapchainKHR> * swapChain;// Swap Chain
		std::vector<VkImage> swapChainImages; // Swap Chain Images
		VkFormat swapChainImageFormat; // Swap Chian Image Format
		VkExtent2D swapChainExtent; // Swap Chain Extent
		std::vector<VDeleter<VkImageView>> swapChainImageViews; // Swap Chain Image Views

		//-----
		VDeleter<VkRenderPass> * renderPass;
		VDeleter<VkPipeline> * graphicsPipeline;

		//---
		std::vector<VDeleter<VkFramebuffer>> swapChainFramebuffers;
		VDeleter<VkCommandPool> * commandPool;
		std::vector<VkCommandBuffer> commandBuffers;

		/* Core Creation Functions */
		void Initialize();
		void createSwapChain();
		void createImageViews();
		void createFramebuffers();
		void createCommandPool();
		void createCommandBuffers();

		/* Helper Functions */
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	};
}
#endif