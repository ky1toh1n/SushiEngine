//V_GRAPHICS_PIPELINE - used to create Graphics Pipelines in Vulkan.
//Currently, only vert and frag shaders are used.

//Cat Note
//Should change VkObjects to be members again but make other classes/objects hold them???
//Fuck pointers!!!
#ifndef V_GRAPHICS_PIPELINE_H
#define V_GRAPHICS_PIPELINE_H

#include <fstream>
#include <vector>
#include <vulkan\vulkan.h>
#include "VDeleter.h"
namespace SushiEngine {
	class VGraphicsPipeline
	{
	public:
		VGraphicsPipeline() = delete;

		//Creational methods
		static VDeleter<VkPipeline> * createGraphicsPipeline(VDeleter<VkDevice> * device, VkExtent2D swapChainExtent, VkRenderPass * renderPass);
		static VkRenderPass * createRenderPass( VDeleter<VkDevice> * device, VkFormat swapChainImageFormat);
	private:
		//Helper methods
		static std::vector<char> readFile(const std::string& filename);
		static void createShaderModule(const std::vector<char>& code, VDeleter<VkShaderModule>& shaderModule, VDeleter<VkDevice>&);
	};
}
#endif