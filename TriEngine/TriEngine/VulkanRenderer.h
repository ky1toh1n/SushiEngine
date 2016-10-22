#ifndef VULKAN_RENDERER
#define VULKAN_RENDERER

#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <functional>

class VulkanRenderer {
public:

	void Run();

private:

	void InitVulkan();
	void MainLoop();

};

#endif