#include "VInitializer.h"


namespace SushiEngine {
	VInitializer::VInitializer()
	{
		Debug::Log(EMessageType::S_INFO, "\t\tVInitializer() ", __FILENAME__, __LINE__);
		CreateVulkanInstance();
		SelectPhysicalDevice();
		CreateLogicalDevice();
	}


	VInitializer::~VInitializer()
	{
		Debug::Log(EMessageType::S_INFO, "\t\t~VInitializer() ", __FILENAME__, __LINE__);
		vkDestroyInstance(instance, NULL);
		//Physical Devices are implicitly destroyed by vkDestroyInstance.
	}

	void VInitializer::CreateVulkanInstance() {
		///---Describes the application
		VkApplicationInfo appInfo;
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;//VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pNext = NULL;
		//The name parameters need a UTF-8 null terminated string, which 'u8' provides.
		appInfo.pApplicationName = u8"Haustastic";
		appInfo.pEngineName = u8"Sushi";
		appInfo.applicationVersion = 0; //TODO Take an application version as a parameter. 
		appInfo.engineVersion = 0; //TODO store an engine version number somewhere.
		appInfo.apiVersion = 0;

		///---Control the creation of the VkInstance
		VkInstanceCreateInfo createInfo;
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;// VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pNext = NULL;
		createInfo.flags = 0; //Reserved for future use
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledLayerCount = 0;
		createInfo.ppEnabledLayerNames = NULL;
		createInfo.enabledExtensionCount = 0;
		createInfo.ppEnabledExtensionNames = NULL;

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
			for (int j = 0; j < propertyCount; j++)
			{
				//TODO: examine the properties to ensure device supports the operations we are interested in.
				//queueProperties[j].queueCount;
			}

			delete[] queueProperties;
		}

		///---Right now, we're fine with any device as long as it works.
		//TODO, select a device most suited for this app.
		physicalDevice = devices[0];

		//Cleanup
		delete[] devices;
	}

	void VInitializer::CreateLogicalDevice() {
		///
		VkDeviceQueueCreateInfo queueInfo;
		queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueInfo.pNext = NULL;
		queueInfo.flags = 0; //reserved for future use
		queueInfo.queueFamilyIndex;
		queueInfo.pQueuePriorities;
		queueInfo.queueCount;

		///Control the creation of the logical device
		VkDeviceCreateInfo deviceInfo;
		deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceInfo.pNext = NULL;
		deviceInfo.flags = 0; //reserved for future use
		deviceInfo.queueCreateInfoCount;
		deviceInfo.pQueueCreateInfos;
		deviceInfo.enabledExtensionCount = 0;
		deviceInfo.ppEnabledExtensionNames = NULL;
		deviceInfo.pEnabledFeatures = NULL;

		HANDLE_VK_RESULT(vkCreateDevice(physicalDevice, &deviceInfo, NULL, &device));
	}
}