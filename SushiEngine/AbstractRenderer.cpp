#include "AbstractRenderer.h"

namespace SushiEngine 
{
	AbstractRenderer::AbstractRenderer(Window* pWindow) : mWindow(pWindow)
	{
	}


	AbstractRenderer::~AbstractRenderer()
	{
	}

	void AbstractRenderer::setCamera(Camera* pCamera) 
	{
		mCamera = pCamera;
	}

/*	Window* AbstractRenderer::getWindow()
	{
		return mWindow;
	}*/
}