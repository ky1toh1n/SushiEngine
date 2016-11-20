/** OpenGLRenderer - A renderer that uses OpenGL and GLFW.*/
#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H
/* System */
#include <iostream>
/* Third Party */
#include "IL\il.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
/* SushiEngine */
#include "AbstractRenderer.h"
#include "Window.h"
#include "SuGameObject.h"
#include "ModelManager.h"
#include "ShaderLoader.h"
/* ---- */
namespace SushiEngine
{
	class OpenGLRenderer : public AbstractRenderer
	{
	public:
		/* Constructor */
		OpenGLRenderer(Window*);
		~OpenGLRenderer();

		/* Instance methods */
		virtual void init();
		virtual void render(SuGameObject* gameObject);
	private:
		/* Instance fields */
		GLuint mModelLocation;
		GLuint mCameraLocation;
		GLuint mProjectionLocation;
		GLuint shaderProgram;
		//temp
		GLfloat rotation = 0;
		GLuint vertexShaderID;
		GLuint fragmentShaderID;
	};
}
#endif