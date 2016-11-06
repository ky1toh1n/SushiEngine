//VInitializer - Initializes the Vulkan context.
//It creates the Vulkan objects that are made only once per program lifetime.
//This includes VkInstance, VkPhysicalDevice, VkDevice


//PROPOSAL: Change Initializer -> Context as a more accurate name?
//TODO: Right now, Queue family selection is hard coded.
//We need to learn more about handling different GPUs and how we want to use the queues.
//We also need to select a queue family for graphics & for presenting, and querying if a queue family can present to the current surface.

#ifndef V_INITIALIZER_H
#define V_INITIALIZER_H

#include "vulkan\vulkan.h"
#include "VHelper.h"
#include "Debug.h"
#include "GLFW\glfw3.h"
#include <string>
#include <vector>

//Debug defines
#define ENABLE_VALIDATION_LAYERS
#define ENABLE_DEBUG_CALLBACK

//Static header for debug callbacks
static VKAPI_ATTR VkBool32 VKAPI_CALL debugReportCallback(
	VkDebugReportFlagsEXT       flags,
	VkDebugReportObjectTypeEXT  objectType,
	uint64_t                    object,
	size_t                      location,
	int32_t                     messageCode,
	const char*                 pLayerPrefix,
	const char*                 pMessage,
	void*                       pUserData);

namespace SushiEngine {
	//Not robust; use glfwGetRequiredInstanceExtensions instead
	const std::vector<const char*> instanceExtensions = {
		u8"VK_KHR_surface",
		u8"VK_KHR_win32_surface",
#ifdef ENABLE_DEBUG_CALLBACK
		u8"VK_EXT_debug_report",
#endif
	};

	const std::vector<const char *> deviceExtensions = {
		u8"VK_KHR_swapchain",
	};

	const std::vector<const char*> validationLayers = {
		//"VK_LAYER_LUNARG_api_dump"
		u8"VK_LAYER_LUNARG_standard_validation",
	};

	class VRenderer;
	class VInitializer
	{
	public:
		VInitializer(GLFWwindow*);
		~VInitializer();

		//Vulkan Objects
		VkInstance instance;
		VkPhysicalDevice physicalDevice;
		VkDevice device;
		VkDebugReportCallbackEXT callback;
		VkSurfaceKHR surface;

		//Selected queue family & accessor
		uint32_t queueFamilyIndex;
		uint32_t queueCount;
	private: 
		//GLFW window
		GLFWwindow* window;

		//Creational methods
		void CreateVulkanInstance();
		void SelectPhysicalDevice();
		void CreateLogicalDevice();
		void CreateDebugCallback();
		void CreateSurface();

		//Helper methods
		void SelectInstanceExtensions();
		void SelectDeviceExtensions();
		void SelectLayers();
	};
}
#endif
