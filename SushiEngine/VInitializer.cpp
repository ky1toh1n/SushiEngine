#include "VInitializer.h"

namespace SushiEngine {

	/*Global Helper Functions*/
	// Default Callback Message
	VKAPI_ATTR VkBool32 VKAPI_CALL VInitializer::debugCallback(
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t obj,
		size_t location,
		int32_t code,
		const char* layerPrefix,
		const char* msg,
		void* userData) {

		Debug::Log(EMessageType::S_ERROR, std::string(msg), __FILENAME__, __LINE__);
		std::cerr << "validation layer: " << msg << std::endl;

		return VK_FALSE;
	}


	// Debug Creation Callback Function
	VkResult VInitializer::CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) {
		auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pCallback);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	// Debug Destruction Callback Function
	void VInitializer::DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
		auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
		if (func != nullptr) {
			func(instance, callback, pAllocator);
		}
	}

	VInitializer::VInitializer()
	{
		throw "This class is not meant to be instantiated.";
	}


	//------------------Creational Methods
	//Create Vulkan Instance
	VDeleter<VkInstance> * VInitializer::createInstance() {
		VDeleter<VkInstance> * instance = new VDeleter<VkInstance>{ vkDestroyInstance }; // Vulkan Instance	

		//Throw an error if validation layers are enabled but aren't supported.
		if (enableValidationLayers && !checkValidationLayerSupport()) {
			throw std::runtime_error("validation layers requested, but not available!");
		}

		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Hello Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Sushi Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		if (enableValidationLayers) {
			createInfo.enabledLayerCount = validationLayers.size();
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else {
			createInfo.enabledLayerCount = 0;
		}

		unsigned int glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		auto extensions = getRequiredExtensions();
		createInfo.enabledExtensionCount = extensions.size();
		createInfo.ppEnabledExtensionNames = extensions.data();

		if (vkCreateInstance(&createInfo, nullptr, instance->replace()) != VK_SUCCESS) {
			throw std::runtime_error("failed to create instance!");
		}

		return instance;
	}

	//Check Validation Layers
	bool VInitializer::checkValidationLayerSupport()
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : validationLayers) {
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers) {
				if (strcmp(layerName, layerProperties.layerName) == 0) {
					layerFound = true;
					break;
				}
			}

			if (!layerFound) {
				return false;
			}
		}

		return true;
	}

	// gets required glfw extensions and validation layers
	std::vector<const char*> VInitializer::getRequiredExtensions() {
		std::vector<const char*> extensions;

		unsigned int glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		for (unsigned int i = 0; i < glfwExtensionCount; i++) {
			extensions.push_back(glfwExtensions[i]);
		}

		if (enableValidationLayers) {
			extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		}

		return extensions;
	}

	// Creates Debug Callback mechanism
	VDeleter<VkDebugReportCallbackEXT> * VInitializer::setupDebugCallback(VDeleter<VkInstance> * instance) {
		VDeleter<VkDebugReportCallbackEXT> * callback = new VDeleter<VkDebugReportCallbackEXT>(*instance, DestroyDebugReportCallbackEXT);

		if (!enableValidationLayers) return nullptr;

		VkDebugReportCallbackCreateInfoEXT createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
		createInfo.pfnCallback = VInitializer::debugCallback;

		if (CreateDebugReportCallbackEXT(*instance, &createInfo, nullptr, callback->replace()) != VK_SUCCESS) {
			throw std::runtime_error("failed to set up debug callback!");
		}

		return callback;
	}

	// Creates Vulkan Surface using GLFW's HWND handle
	VDeleter<VkSurfaceKHR> * VInitializer::createSurface(VDeleter<VkInstance> * instance,
		GLFWwindow* window)
	{
		VDeleter<VkSurfaceKHR> * surface = new VDeleter<VkSurfaceKHR>(*instance, vkDestroySurfaceKHR);

		if (glfwCreateWindowSurface(*instance, window, nullptr, surface->replace()) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}

		return surface;
	}

	// Pick Physical Device
	VkPhysicalDevice VInitializer::pickPhysicalDevice(VDeleter<VkInstance> * instance, VDeleter<VkSurfaceKHR> * surface)
	{
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE; // Physical Graphics Device		

		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(*instance, &deviceCount, nullptr);
		if (deviceCount == 0) {
			Debug::Log(EMessageType::S_FATAL_ERROR, "Failed to find GPUs with Vulkan Support.", __FILENAME__, __LINE__);
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(*instance, &deviceCount, devices.data());

		for (VkPhysicalDevice device : devices) {
			if (isDeviceSuitable(device, surface)) {
				physicalDevice = device;
				break;
			}
		}

		if (physicalDevice == VK_NULL_HANDLE) {
			Debug::Log(EMessageType::S_FATAL_ERROR, "Failed to find a suitable GPU.", __FILENAME__, __LINE__);
		}

		return physicalDevice;
	}

	// Checks if a device is suitable for this surface
	bool VInitializer::isDeviceSuitable(VkPhysicalDevice device, VDeleter<VkSurfaceKHR> * surface)
	{
		QueueFamilyIndices indices = findQueueFamilies(device, surface);

		bool extensionsSupported = checkDeviceExtensionSupport(device);

		bool swapChainAdequate = false;
		if (extensionsSupported) {
			SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device, surface);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}

		return indices.isComplete() && extensionsSupported && swapChainAdequate;
	} 

	// Creates a Logical Device, and graphics and present queue along with it.
	VDeleter<VkDevice> * VInitializer::createLogicalDevice(VkPhysicalDevice physicalDevice, VkQueue graphicsQueue,
		VkQueue presentQueue, VDeleter<VkSurfaceKHR> * surface)
	{
		VDeleter<VkDevice> * device = new VDeleter<VkDevice>{ vkDestroyDevice };

		QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface);
		/*
		Vulkan lets you assign priorities to queues to influence the scheduling of command buffer execution using
		floating point numbers between 0.0 and 1.0. This is required even if there is only a single queue:

		https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Logical_device_and_queues
		*/
		float queuePriority = 1.0f;

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<int> uniqueQueueFamilies = { indices.graphicsFamily, indices.presentFamily };

		for (int queueFamily : uniqueQueueFamilies) {
			VkDeviceQueueCreateInfo queueCreateInfo = {};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures deviceFeatures = {};

		VkDeviceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.queueCreateInfoCount = (uint32_t)queueCreateInfos.size();
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = deviceExtensions.size();
		createInfo.ppEnabledExtensionNames = deviceExtensions.data();

		if (enableValidationLayers) {
			createInfo.enabledLayerCount = validationLayers.size();
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else {
			createInfo.enabledLayerCount = 0;
		}

		if (vkCreateDevice(physicalDevice, &createInfo, nullptr, device->replace()) != VK_SUCCESS) {
			throw std::runtime_error("failed to create logical device!");
		}

		vkGetDeviceQueue(*device, indices.graphicsFamily, 0, &graphicsQueue);
		vkGetDeviceQueue(*device, indices.presentFamily, 0, &presentQueue);

		return device;
	}

	//Finds the queue family for a physical device
	QueueFamilyIndices VInitializer::findQueueFamilies(VkPhysicalDevice device, VDeleter<VkSurfaceKHR> * surface)
	{
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				indices.graphicsFamily = i;
			}

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, *surface, &presentSupport);

			if (queueFamily.queueCount > 0 && presentSupport) {
				indices.presentFamily = i;
			}

			if (indices.isComplete()) {
				break;
			}
			i++;
		}

		return indices;
	}

	// Checks if extensions are supported by this physical device
	bool VInitializer::checkDeviceExtensionSupport(VkPhysicalDevice device)
	{
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

		std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

		for (const auto& extension : availableExtensions) {
			requiredExtensions.erase(extension.extensionName);
		}

		return requiredExtensions.empty();
	}

	// Queries if this physical device supports a swap chain.
	SwapChainSupportDetails VInitializer::querySwapChainSupport(VkPhysicalDevice device, VDeleter<VkSurfaceKHR> * surface)
	{
		SwapChainSupportDetails details;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, *surface, &details.capabilities);

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, *surface, &formatCount, nullptr);

		if (formatCount != 0) {
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, *surface, &formatCount, details.formats.data());
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, *surface, &presentModeCount, nullptr);

		if (presentModeCount != 0) {
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, *surface, &presentModeCount, details.presentModes.data());
		}

		return details;
	}
}