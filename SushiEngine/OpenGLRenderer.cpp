#include "OpenGLRenderer.h"



namespace SushiEngine {
	OpenGLRenderer::OpenGLRenderer(Window* window) : AbstractRenderer(window)
	{
	}


	OpenGLRenderer::~OpenGLRenderer()
	{
	}

	void OpenGLRenderer::render()
	{
		glfwSwapBuffers(window->GetWindowHandle());
		//Do all the magic here!
		//window->
		//glfwSwapBuffers(window->GetWindowHandle());
	}
}