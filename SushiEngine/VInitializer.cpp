#include "VInitializer.h"

//
static VKAPI_ATTR VkBool32 VKAPI_CALL debugReportCallback(
	VkDebugReportFlagsEXT       flags,
	VkDebugReportObjectTypeEXT  objectType,
	uint64_t                    object,
	size_t                      location,
	int32_t                     messageCode,
	const char*                 pLayerPrefix,
	const char*                 pMessage,
	void*                       pUserData)
{
	//TODO use the parameters to make better messages, such as which flag triggered it
	std::cerr << pMessage << std::endl;
	return VK_FALSE;
}

namespace SushiEngine {
	

	VInitializer::VInitializer(GLFWwindow* window) : window(window)
	{
		Debug::Log(EMessageType::S_INFO, "\t\tVInitializer() ", __FILENAME__, __LINE__);
		SelectInstanceExtensions();
#ifdef ENABLE_VALIDATION_LAYERS
		SelectLayers();
#endif
		CreateVulkanInstance();
#ifdef ENABLE_DEBUG_CALLBACK
		CreateDebugCallback();
#endif
		SelectPhysicalDevice();
		CreateSurface();
		SelectDeviceExtensions();
		CreateLogicalDevice();
	}

	VInitializer::~VInitializer()
	{
		Debug::Log(EMessageType::S_INFO, "\t\t~VInitializer() ", __FILENAME__, __LINE__);
		//Queues are destroyed when logical devices are destroyed
		vkDestroyDevice(device, nullptr);
		vkDestroySurfaceKHR(instance, surface, nullptr);
#ifdef ENABLE_DEBUG_CALLBACK
		PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT =
			reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>
			(vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT"));
		vkDestroyDebugReportCallbackEXT(instance, callback, nullptr);
#endif
		//Physical Devices are implicitly destroyed by vkDestroyInstance.
		vkDestroyInstance(instance, nullptr);
	}

	void VInitializer::CreateDebugCallback() {
		PFN_vkDebugReportMessageEXT vkDebugReportMessageEXT =
			reinterpret_cast<PFN_vkDebugReportMessageEXT>
			(vkGetInstanceProcAddr(instance, "vkDebugReportMessageEXT"));
		
		//HANDLE_VK_RESULT(vkCreateInstance(&createInfo, nullptr, &instance));
		VkDebugReportCallbackCreateInfoEXT createInfo;
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
		createInfo.pNext = nullptr;
		createInfo.flags = 
			/*VK_DEBUG_REPORT_INFORMATION_BIT_EXT |*/
			VK_DEBUG_REPORT_WARNING_BIT_EXT |
			VK_DEBUG_REPORT_ERROR_BIT_EXT |
			VK_DEBUG_REPORT_WARNING_BIT_EXT |
			VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
		createInfo.pfnCallback = &debugReportCallback;
		createInfo.pUserData = nullptr; //Data passed to the callback.

		PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT =
			reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>
			(vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT"));
		HANDLE_VK_RESULT(vkCreateDebugReportCallbackEXT(instance, &createInfo, nullptr, &callback));
	}

	void VInitializer::SelectInstanceExtensions()
	{		
		///Query for available extensions
		uint32_t propertyCount;
		VkExtensionProperties* properties;
		vkEnumerateInstanceExtensionProperties(nullptr, &propertyCount, nullptr);
		properties = new VkExtensionProperties[propertyCount];
		vkEnumerateInstanceExtensionProperties(nullptr, &propertyCount, properties);

		///See if desired extensions are within the available extensions
		Debug::Print("---Desired Instance Extensions");
		for (int i = 0; i < instanceExtensions.size(); i++) {
			std::string currentExtension = std::string(instanceExtensions[i]);
			Debug::Print(currentExtension);
			bool extensionFound = false;

			//Check this extension against all the available extensions
			for (int j = 0; j < propertyCount; j++)
			{
				if (currentExtension.compare(properties[j].extensionName) == 0) {
					extensionFound = true;
					break;
				}//if
			}//for

			//Failure!
			if (!extensionFound) {
				Debug::Log(EMessageType::S_ERROR, "\t\tVInitializer/SelectInstanceExtensions(): Could not get all required extensions.", __FILENAME__, __LINE__);
				throw "Failed to find all requested instance extensions.";
			}
		}//for
	
		///Glfw required extensions
		/*unsigned int glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		for (unsigned int i = 0; i < glfwExtensionCount; i++) {
			std::cout << glfwExtensions[i] << std::endl;
		}*/
	}

	void VInitializer::SelectDeviceExtensions()
	{
		///Query for available extensions
		uint32_t propertyCount;
		VkExtensionProperties* properties;
		vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &propertyCount, nullptr);
		properties = new VkExtensionProperties[propertyCount];
		vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &propertyCount, properties);

		/* Check for available device extensions
		for (int a = 0; a < propertyCount; a++) {
			std::cout << properties[a].extensionName << std::endl;
		}*/

		///See if desired extensions are within the available extensions
		Debug::Print("---Desired Device Extensions");
		for (int i = 0; i < deviceExtensions.size(); i++) {
			std::string currentExtension = std::string(deviceExtensions[i]);
			Debug::Print(currentExtension);
			bool extensionFound = false;

			//Check this extension against all the available extensions
			for (int j = 0; j < propertyCount; j++)
			{
				if (currentExtension.compare(properties[j].extensionName) == 0) {
					extensionFound = true;
					break;
				}//if
			}//for

			 //Failure!
			if (!extensionFound) {
				Debug::Log(EMessageType::S_ERROR, "\t\tVInitializer/SelectDeviceExtensions(): Could not get all required extensions.", __FILENAME__, __LINE__);
				throw "Failed to find all requested instance extensions.";
			}
		}//for

	}

	void VInitializer::SelectLayers()
	{
		///Query for available layers
		uint32_t propertyCount;
		VkLayerProperties* properties;
		vkEnumerateInstanceLayerProperties(&propertyCount, nullptr);
		properties = new VkLayerProperties[propertyCount];
		vkEnumerateInstanceLayerProperties(&propertyCount, properties);

		///See if desired layers are within the available layers 
		Debug::Print("---Desired Layers");
		for (int i = 0; i <  validationLayers.size(); i++) {
			std::string currentLayer = std::string(validationLayers[i]);
			Debug::Print(currentLayer);
			bool layerFound = false;

			//Check this layer against all the avilable layers
			for (int j = 0; j < propertyCount; j++)
			{
				if (currentLayer.compare(properties[j].layerName) == 0) {
					layerFound = true;
					break;
				}//if
			}//for

			 //Failure!
			if (!layerFound) {
				Debug::Log(EMessageType::S_ERROR, "\t\tVInitializer/SelectLayers(): Could not get all required validation layers.", __FILENAME__, __LINE__);
				throw "Failed to find all requested validation layers.";
			}
		}//fo
	}

	void VInitializer::CreateVulkanInstance() {
		///---Describes the application
		VkApplicationInfo appInfo;
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;//VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pNext = nullptr;
		//The name parameters need a UTF-8 null terminated string, which 'u8' provides.
		appInfo.pApplicationName = u8"Haustastic";
		appInfo.pEngineName = u8"Sushi";
		appInfo.applicationVersion = 0; //TODO Take an application version as a parameter. 
		appInfo.engineVersion = 0; //TODO store an engine version number somewhere.
		appInfo.apiVersion = 0;

		///---Control the creation of the VkInstance
		VkInstanceCreateInfo createInfo;
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;// VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pNext = nullptr;
		createInfo.flags = 0; //Reserved for future use
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = createInfo.enabledLayerCount > 0
			? &validationLayers[0] : nullptr;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
		createInfo.ppEnabledExtensionNames = createInfo.enabledExtensionCount > 0
			? instanceExtensions.data() : nullptr;

		///---Create the VkInstance!!!
		HANDLE_VK_RESULT(vkCreateInstance(&createInfo, nullptr, &instance));
	}

	void VInitializer::SelectPhysicalDevice() {
		///---Get information about all physical devices on this machine
		uint32_t deviceCount = 0;
		VkPhysicalDevice* devices;

		//Query for device count
		HANDLE_VK_RESULT(vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr));

		//Create array to hold physical devices, and query for devices
		devices = new VkPhysicalDevice[deviceCount];
		HANDLE_VK_RESULT(vkEnumeratePhysicalDevices(instance, &deviceCount, devices));

		//Complain if there's no suitable device
		if (deviceCount == 0) {
			throw "This computer does not support Vulkan.";
		}

		///---Check the properties of each device
		for (int i = 0; i < deviceCount; i++)
		{
			//Get properties of this device
			VkPhysicalDeviceProperties deviceProperties;
			vkGetPhysicalDeviceProperties(devices[i], &deviceProperties);

			//Get properties from all queue families of this device
			uint32_t propertyCount;
			VkQueueFamilyProperties* queueProperties;
			vkGetPhysicalDeviceQueueFamilyProperties(devices[i], &propertyCount, NULL);
			queueProperties = new VkQueueFamilyProperties[propertyCount];
			vkGetPhysicalDeviceQueueFamilyProperties(devices[i], &propertyCount, queueProperties);

			//Check the properties of each queue family
			for (int j = propertyCount - 1; j >= 0; j--)
			//for (int j = 0; j < propertyCount; j++)
			{
				//TODO: examine the properties to ensure device supports the operations we are interested in.
				///Save the queue family index & its count.
				queueFamilyIndex = j;
				queueCount = queueProperties[j].queueCount;
			}

			delete[] queueProperties;
		}

		///---Select a physical device
		//TODO, select a device most suited for this app.
		physicalDevice = devices[0];

		//Cleanup
		delete[] devices;
	}

	void VInitializer::CreateLogicalDevice() {
		//TODO: Decide better on how many queues and queue families to use.
		//It's a problem if we work on a machine with only 1 queue... do we want to support it?
		//For now, let's go with one family and its queues (assuming 16 for NVidia)

		///Assign queue priorities
		float * pQueuePriorities = new float[queueCount];
		for (int i = 0; i < queueCount; i++) {
			pQueuePriorities[i] = 1.0f;
		}

		///Control creation of queues within a specified queue family
		VkDeviceQueueCreateInfo queueInfo;
		queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueInfo.pNext = nullptr;
		queueInfo.flags = 0; //reserved for future use
		queueInfo.queueFamilyIndex = queueFamilyIndex;
		queueInfo.pQueuePriorities = pQueuePriorities;
		queueInfo.queueCount = queueCount;

		///Logical device features
		VkPhysicalDeviceFeatures deviceFeatures = {};

		///Control the creation of the logical device
		VkDeviceCreateInfo deviceInfo;
		deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceInfo.pNext = nullptr;
		deviceInfo.flags = 0; //reserved for future use
		deviceInfo.queueCreateInfoCount = static_cast<uint32_t>(1);
		deviceInfo.pQueueCreateInfos = &queueInfo;
		deviceInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
		deviceInfo.ppEnabledExtensionNames = deviceExtensions.data();
		deviceInfo.pEnabledFeatures = &deviceFeatures;
		deviceInfo.enabledLayerCount = validationLayers.size();
		deviceInfo.ppEnabledLayerNames = validationLayers.data();

		HANDLE_VK_RESULT(vkCreateDevice(physicalDevice, &deviceInfo, nullptr, &device));
	}

	void VInitializer::CreateSurface() {
		HANDLE_VK_RESULT(glfwCreateWindowSurface(instance, window, nullptr, &surface));
	}
}