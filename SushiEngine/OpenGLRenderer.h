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
		virtual void render(vector<SuGameObject*> gameObjects);

		GLuint location;
		GLuint location2;
		GLuint location3;

		GLuint lightPositionUniformLocation;
		GLuint ambientUniformLocation;
		GLuint diffuseUniformLocation;

		GLuint program;

		GLuint vertexShaderID;
		GLuint fragmentShaderID;
	};
}
#endif