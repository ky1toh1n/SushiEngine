#include "VRenderer.h"

namespace SushiEngine {

	/************** Vulkan Renderer Class ****************/

	VRenderer::VRenderer(GLFWwindow* window) : _window(window)
	{
		Debug::Log(EMessageType::S_INFO, "\tVRenderer", __FILENAME__, __LINE__);
		initializer = new VInitializer();
		commander = new VCommander(initializer->queueFamilyIndex, initializer->device);
	}

	VRenderer::~VRenderer()
	{
		Debug::Log(EMessageType::S_INFO, "\t~VRenderer()", __FILENAME__, __LINE__);
		delete commander;
		delete initializer;
	}
}