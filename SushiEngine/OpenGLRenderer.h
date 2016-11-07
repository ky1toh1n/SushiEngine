//OpenGLRenderer - A renderer that uses OpenGL. (interfaced through GLFW)
#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include "AbstractRenderer.h"
#include "Window.h"

namespace SushiEngine {
	class OpenGLRenderer : public AbstractRenderer
	{
	public:
		OpenGLRenderer(Window*);
		~OpenGLRenderer();

		virtual void render();
	};
}
#endif