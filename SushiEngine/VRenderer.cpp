#include "VRenderer.h"

namespace SushiEngine {

	/************** Vulkan Renderer Class ****************/

	VRenderer::VRenderer(GLFWwindow* window) : _window(window)
	{
		Debug::Log(EMessageType::S_INFO, "\tVRenderer", __FILENAME__, __LINE__);
	}

	VRenderer::~VRenderer()
	{
		Debug::Log(EMessageType::S_INFO, "\t~VRenderer()", __FILENAME__, __LINE__);
	}
}