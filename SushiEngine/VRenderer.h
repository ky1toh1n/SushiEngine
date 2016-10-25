#ifndef VRENDERER_H
#define VRENDERER_H
#include <chrono>
#include "vulkan/vulkan.h"
#include "Debug.h"
#include "GLFW\glfw3.h"
#include "VDeleter.h"
#include "VStructs.h"
#include <vector>
#include <set>
#include <algorithm>

namespace SushiEngine {
	//Global helper functions
	std::vector<const char*> getRequiredExtensions();
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData);
	void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);
	VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);

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

		VDeleter<VkInstance> instance{ vkDestroyInstance }; // Vulkan Instance		
		VDeleter<VkDebugReportCallbackEXT> callback{ instance, DestroyDebugReportCallbackEXT }; // Debug Callback		
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE; // Physical Graphics Device		
		VDeleter<VkDevice> device{ vkDestroyDevice }; // Logical Graphics Device
		VkQueue graphicsQueue; // Graphics Queue Handle
		VDeleter<VkSurfaceKHR> surface{ instance, vkDestroySurfaceKHR }; // Surface
		VkQueue presentQueue; // Presentation Queue
		VDeleter<VkSwapchainKHR> swapChain{ device, vkDestroySwapchainKHR }; // Swap Chain
		std::vector<VkImage> swapChainImages; // Swap Chain Images
		VkFormat swapChainImageFormat; // Swap Chian Image Format
		VkExtent2D swapChainExtent; // Swap Chain Extent
		std::vector<VDeleter<VkImageView>> swapChainImageViews; // Swap Chain Image Views

		void Initialize();

		/* Core Creation Functions */
		void createInstance();
		void setupDebugCallback();
		void createSurface();
		void pickPhysicalDevice();
		void createLogicalDevice();
		void createSwapChain();
		void createImageViews();
		void createGraphicsPipeline();

		/* Helper Functions */
		bool checkValidationLayerSupport();
		bool isDeviceSuitable(VkPhysicalDevice device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);

		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);		
	};
}
#endif