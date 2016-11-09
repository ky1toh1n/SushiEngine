//OpenGLRenderer - A renderer that uses OpenGL. (interfaced through GLFW)
#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H


#include <iostream>
#include "AbstractRenderer.h"
#include "Window.h"

// #include "vgl.h" // uses free glut -.-'
// #include "VertexShaderCodeRaw.h"
// #include "LoadShaders.cpp"
#include <GL/glew.h>
//#include <GL/gl.h>

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

namespace SushiEngine {

	class OpenGLRenderer : public AbstractRenderer
	{
	public:
		OpenGLRenderer(Window*);
		~OpenGLRenderer();

		virtual void init();
		virtual void render();

		// Manual Load Test
		char* vertexShaderCode =
			"#version 430\r\n"
			""
			"layout(location = 0) in vec4 vPosition;"
			"layout(location = 1) in vec4 vertexColor;"
			""
			"uniform mat4 model_matrix;"
			"uniform mat4 camera_matrix;"
			"uniform mat4 projection_matrix;"
			""
			"out vec4 myColor;"
			""
			"void main()"
			"{"
			"    myColor = vertexColor;"
			"    gl_Position = projection_matrix * camera_matrix * model_matrix * vPosition;"
			"}";

		char* fragmentShaderCode =
			"#version 430\r\n"
			""
			"in vec4 myColor;"
			"out vec4 fColor;"
			""
			"void main()"
			"{"
			"    fColor = myColor;"
			"}";
		

		GLuint buffers[2];
		GLuint location;
		GLuint location2;
		GLuint location3;
		GLuint program;
	};
}
#endif