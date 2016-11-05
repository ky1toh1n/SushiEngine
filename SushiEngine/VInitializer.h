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
	//Not cross-platform friendly; use glfwGetRequiredInstanceExtensions instead
	const std::vector<const char*> desiredExtensions = {
		"VK_KHR_surface",
		"VK_KHR_win32_surface",
#ifdef ENABLE_DEBUG_CALLBACK
		"VK_EXT_debug_report"
#endif
	};

	const std::vector<const char*> desiredValidationLayers = {
		//"VK_LAYER_LUNARG_api_dump"
		"VK_LAYER_LUNARG_standard_validation"
	};

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
		VkDebugReportCallbackEXT callback;

		//Selected queue family & accessor
		uint32_t queueFamilyIndex;
		uint32_t queueCount;
		void getQueue(VkQueue* queueHandle, uint32_t queueIndex);

	private:
		//Enabled extensions & layers
		std::vector<const char*> extensions;
		std::vector<const char*> validationLayers;

		//Creational methods
		void CreateVulkanInstance();
		void SelectPhysicalDevice();
		void CreateLogicalDevice();
		void CreateDebugCallback();

		//Helper methods
		void SelectExtensions();
		void SelectLayers();
	};
}
#endif
