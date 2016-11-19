//OpenGLRenderer - A renderer that uses OpenGL. (interfaced through GLFW)
#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <iostream>

#include "IL\il.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

#include "AbstractRenderer.h"
#include "Window.h"
#include "SuGameObject.h"
#include "ModelManager.h"

#include "ShaderLoader.h"

namespace SushiEngine
{
	class OpenGLRenderer : public AbstractRenderer
	{
	public:
		OpenGLRenderer(Window*);
		~OpenGLRenderer();

		virtual void init();
		virtual void render(SuGameObject* gameObject);

		// fColor = vec4( 1.0, 0.0, 0.0, 1.0 );"
		// fColor = texture2D(texture, texCoord);"

		GLuint buffers[3];
		GLuint location;
		GLuint location2;
		GLuint location3;
		GLuint program;
		GLuint texture[1];

		GLuint mTextureID;
		GLfloat rotation = 0;

		GLuint vertexShaderID;
		GLuint fragmentShaderID;
	};
}
#endif