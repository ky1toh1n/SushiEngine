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
	std::cerr << pMessage << std::endl;
	return VK_FALSE;
}

namespace SushiEngine {
	

	VInitializer::VInitializer()
	{
		Debug::Log(EMessageType::S_INFO, "\t\tVInitializer() ", __FILENAME__, __LINE__);
		SelectExtensions();
#ifdef ENABLE_VALIDATION_LAYERS
		SelectLayers();
#endif
		CreateVulkanInstance();
#ifdef ENABLE_DEBUG_CALLBACK
		CreateDebugCallback();
#endif
		SelectPhysicalDevice();
		CreateLogicalDevice();
	}

	VInitializer::~VInitializer()
	{
		Debug::Log(EMessageType::S_INFO, "\t\t~VInitializer() ", __FILENAME__, __LINE__);
		//Queues are destroyed when logical devices are destroyed
		vkDestroyDevice(device, NULL);
#ifdef ENABLE_DEBUG_CALLBACK
		PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT =
			reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>
			(vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT"));
		vkDestroyDebugReportCallbackEXT(instance, callback, nullptr);
#endif
		//Physical Devices are implicitly destroyed by vkDestroyInstance.
		vkDestroyInstance(instance, NULL);
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
			VK_DEBUG_REPORT_INFORMATION_BIT_EXT |
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

	void VInitializer::SelectExtensions()
	{
		//TODO: Use V-Tutorial's way of using for arrays and bools.
		//There's no need to create an extra Extension/Layer member either!
		//Make the constants static too.

		///Query for available extensions
		uint32_t propertyCount;
		VkExtensionProperties* properties;
		vkEnumerateInstanceExtensionProperties(NULL, &propertyCount, NULL);
		properties = new VkExtensionProperties[propertyCount];
		vkEnumerateInstanceExtensionProperties(NULL, &propertyCount, properties);

		Debug::Print("---Available Extensions");
		///See if desired extensions are within the available extensions
		for (int i = 0; i < propertyCount; i++) {
			std::string currentExtension = std::string(properties[i].extensionName);
			Debug::Print(currentExtension);

			//Check this extension against all the desired extensions
			for (int j = 0; j < desiredExtensions.size(); j++)
			{
				//Debug::Print("\t" + std::string(desiredExtensions[j]));
				if (currentExtension.compare(desiredExtensions[j]) == 0) {
					extensions.push_back(desiredExtensions[j]);
				}//if
			}//for
		}//for

		///If we couldn't find all of the extensions, complain
		if (extensions.size() != desiredExtensions.size()) {
			Debug::Log(EMessageType::S_FATAL_ERROR, "\t\tVInitializer()/SelectExtensions ", __FILENAME__, __LINE__);
			throw "Could not find all the desired extensions!";
		}
	}

	void VInitializer::SelectLayers()
	{
		///Query for available layers
		uint32_t propertyCount;
		VkLayerProperties* properties;
		vkEnumerateInstanceLayerProperties(&propertyCount, NULL);
		properties = new VkLayerProperties[propertyCount];
		vkEnumerateInstanceLayerProperties(&propertyCount, properties);

		Debug::Print("---Available Layers");
		///See if desired layers are within the available layers
		for (int i = 0; i < propertyCount; i++) {
			std::string currentLayer = std::string(properties[i].layerName);
			Debug::Print(currentLayer);

			//Check this layer against all the desired layers
			for (int j = 0; j < desiredValidationLayers.size(); j++)
			{
				//Debug::Print("\t" + std::string(desiredValidationLayers[j]));
				if (currentLayer.compare(desiredValidationLayers[j]) == 0) {
					validationLayers.push_back(desiredValidationLayers[j]);
				}//if
			}//for
		}//for

		 ///If we couldn't find all of the layers, complain
		if (validationLayers.size() != desiredValidationLayers.size()) {
			Debug::Log(EMessageType::S_FATAL_ERROR, "\t\tVInitializer()/SelectLayers ", __FILENAME__, __LINE__);
			throw "Could not find all the desired layers!";
		}

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
			? &validationLayers[0] : NULL;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = createInfo.enabledExtensionCount > 0
			? extensions.data() : NULL;;

		///---Create the VkInstance!!!
		HANDLE_VK_RESULT(vkCreateInstance(&createInfo, nullptr, &instance));
	}

	void VInitializer::SelectPhysicalDevice() {
		///---Get information about all physical devices on this machine
		uint32_t deviceCount = 0;
		VkPhysicalDevice* devices;

		//Query for device count
		HANDLE_VK_RESULT(vkEnumeratePhysicalDevices(instance, &deviceCount, NULL));

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
			{
				//TODO: examine the properties to ensure device supports the operations we are interested in.
				///Save the queue family index & its count.
				queueFamilyIndex = 0;
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

	void VInitializer::getQueue(VkQueue * queueHandle, uint32_t queueIndex) {

		if (queueIndex >= queueCount) {
			Debug::Log(EMessageType::S_FATAL_ERROR, "\t\tVInitializer()/getQueue ", __FILENAME__, __LINE__);
			throw "This queue index: " + std::to_string(queueIndex) + " does not exist on this queue family.";
		}

		vkGetDeviceQueue(device, queueFamilyIndex, queueIndex, queueHandle);
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

		///Control the creation of the logical device
		VkDeviceCreateInfo deviceInfo;
		deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceInfo.pNext = nullptr;
		deviceInfo.flags = 0; //reserved for future use
		deviceInfo.queueCreateInfoCount = 1;
		deviceInfo.pQueueCreateInfos = &queueInfo;
		deviceInfo.enabledExtensionCount = 0;
		deviceInfo.ppEnabledExtensionNames = NULL;
		deviceInfo.pEnabledFeatures = NULL;

		HANDLE_VK_RESULT(vkCreateDevice(physicalDevice, &deviceInfo, NULL, &device));
	}
}