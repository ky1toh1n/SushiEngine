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
#include "InputManager.h"
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
	private:
		/* Instance fields */
		GLuint mModelLocation;
		GLuint mCameraLocation;
		GLuint mProjectionLocation;

		GLuint lightPositionUniformLocation;
		GLuint ambientUniformLocation;
		GLuint diffuseUniformLocation;

		GLuint programID;

		GLuint vertexShaderID;
		GLuint fragmentShaderID;


		GLfloat lightX = -10.0f;
		bool goingright = true;

		/* Instance methods */
		GLuint EZSHADING(SuShaderType pShaderType, const char * pFilePath, GLenum pFlShaderType, GLenum pShaderProgram);
		virtual void render(vector<SuGameObject*> gameObjects);
	};
}
#endif