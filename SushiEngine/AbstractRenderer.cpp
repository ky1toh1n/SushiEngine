#include "AbstractRenderer.h"

namespace SushiEngine
{
	AbstractRenderer::AbstractRenderer(Window* window) : window(window)
	{
	}


	AbstractRenderer::~AbstractRenderer()
	{
	}

	void AbstractRenderer::setCamera(Camera* pCamera)
	{
		camera = pCamera;
	}
}