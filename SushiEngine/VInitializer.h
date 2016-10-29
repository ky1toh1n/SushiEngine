// V-INITIALIZER - Initializes the Vulkan instance, surfaces, and devices. 
//Initializes things that only need to be made once every time the application runs.

//This class is abstract, and is not meant to be instantiated ever.
#ifndef V_INITIALIZER_H
#define V_INITIALIZER_H

#include "vulkan\vulkan.h"
#include "VDeleter.h"
#include "GLFW\glfw3.h"
#include <vector>
#include "Debug.h"
#include "VStructs.h"
#include <set>

namespace SushiEngine {
	class VInitializer
	{
	public:
		VInitializer() = delete;

		//Core creation functions
		static VDeleter<VkInstance> * createInstance();
		static VDeleter<VkDebugReportCallbackEXT> * setupDebugCallback(VDeleter<VkInstance> *);
		static VDeleter<VkSurfaceKHR> * createSurface(VDeleter<VkInstance> *,GLFWwindow*);
		static VkPhysicalDevice pickPhysicalDevice(VDeleter<VkInstance> *, VDeleter<VkSurfaceKHR> *);
		static VDeleter<VkDevice> * createLogicalDevice(VkPhysicalDevice , VkQueue graphicsQueue,VkQueue presentQueue, VDeleter<VkSurfaceKHR> *);

		//Public helper functions
		static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice  device, VDeleter<VkSurfaceKHR> *);
		static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VDeleter<VkSurfaceKHR> * surface);
	private:
		//----------------------Helper functions
		static bool checkValidationLayerSupport();
		static std::vector<const char*> getRequiredExtensions();
		static bool isDeviceSuitable(VkPhysicalDevice device, VDeleter<VkSurfaceKHR> * surface);

		//Debug callback
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData);
		static VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);
		static void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);
		
		//Queue, Swapchain and Logical Device
		static bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	};
}
#endif