#ifndef VK_RENDERER_H
#define VK_RENDERER_H
#include <chrono>
#include "vulkan/vulkan.h"
#include "Debug.h"
#include "GLFW\glfw3.h"
#include "VDeleter.h"
#include <vector>

namespace SushiEngine {
	//Global helper functions
	std::vector<const char*> getRequiredExtensions();

	//void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t obj,
		size_t location,
		int32_t code,
		const char* layerPrefix,
		const char* msg,
		void* userData);

	
	VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);
	//---------------------------------------------
	class VkRenderer
	{
	public:
		VkRenderer();
		~VkRenderer();

	private:
		//Helper Functions
		bool checkValidationLayerSupport();

		//Fields
		VDeleter<VkInstance> instance{ vkDestroyInstance };
		VkDebugReportCallbackEXT callback;
		
		//Core creational functions
		void createInstance();
		void setupDebugCallback();

	};


}
#endif