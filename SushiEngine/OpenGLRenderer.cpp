#include "OpenGLRenderer.h"

namespace SushiEngine {

	OpenGLRenderer::OpenGLRenderer(Window* window) : AbstractRenderer(window)
	{
		init();
	}


	OpenGLRenderer::~OpenGLRenderer()
	{
	}

	void OpenGLRenderer::init() {

		/* Testing Manual Loading of Shaders
		GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		char* adapter[1];
		adapter[0] = vertexShaderCode;
		glShaderSource(vertexShaderID, 1, adapter, 0);
		adapter[0] = fragmentShaderCode;
		glShaderSource(fragmentShaderID, 1, adapter, 0);

		glCompileShader(vertexShaderID);
		glCompileShader(fragmentShaderID);

		program = glCreateProgram();
		glAttachShader(program, vertexShaderID);
		glAttachShader(program, fragmentShaderID);

		glLinkProgram(program);
		glUseProgram(program);	//My Pipeline is set up
		*/

		/* Ali's Way

		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "triangles.vert" },
			{ GL_FRAGMENT_SHADER, "triangles.frag" },
			{ GL_NONE, NULL }
		};

		program = LoadShaders(shaders);
		glUseProgram(program);	//My Pipeline is set up

		*/

		/*
		const GLuint numVerts = 16;
		GLfloat cubeVerts[numVerts][3] = {
			{ -0.05, +0.05, -0.05 }, // B
			{ +0.05, +0.05, -0.05 },
			{ +0.05, -0.05, -0.05 },
			{ -0.05, -0.05, -0.05 },

			{ -0.05, +0.05, +0.05 }, // F
			{ +0.05, +0.05, +0.05 },
			{ +0.05, -0.05, +0.05 },
			{ -0.05, -0.05, +0.05 },

			{ +0.05, +0.05, +0.05 }, // R
			{ +0.05, +0.05, -0.05 },
			{ +0.05, -0.05, -0.05 },
			{ +0.05, -0.05, +0.05 },

			{ -0.05, +0.05, +0.05 }, // L
			{ -0.05, +0.05, -0.05 },
			{ -0.05, -0.05, -0.05 },
			{ -0.05, -0.05, +0.05 },
		};

		GLfloat cubeVertsColor[numVerts][3] = {
			{ 0,1,0 },
			{ 0,1,0 },
			{ 0,1,0 },
			{ 0,1,0 },

			{ 0,1,0 },
			{ 0,1,0 },
			{ 0,1,0 },
			{ 0,1,0 },

			{ 0,0.7,1 },
			{ 0,0.7,1 },
			{ 0,0.7,1 },
			{ 0,0.7,1 },

			{ 0,0.7,1 },
			{ 0,0.7,1 },
			{ 0,0.7,1 },
			{ 0,0.7,1 }
		};


		// Enable Depth Culling
		glEnable(GL_DEPTH_TEST);


		// Generate Paddle Buffers and Send Data to GPU
		glGenBuffers(2, buffers);

		// Generate Ball Buffers and Send Data to GPU
		glGenBuffers(2, buffers);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts), cubeVerts, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertsColor), cubeVertsColor, GL_STATIC_DRAW);

		location = glGetUniformLocation(program, "model_matrix");
		location2 = glGetUniformLocation(program, "camera_matrix");
		location3 = glGetUniformLocation(program, "projection_matrix");
		*/
	}


	void OpenGLRenderer::render()
	{
		/*
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Switch buffer binding point
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		// Set pointer to start of buffer attrib
		glEnableVertexAttribArray(0);
		// Describe how data is read
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const void*)0);

		glm::mat4 model_view = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 0));
		model_view = glm::rotate(model_view, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(location, 1, GL_FALSE, &model_view[0][0]);

		glm::mat4 camera_matrix = glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 1.0, 0.0));
		glUniformMatrix4fv(location2, 1, GL_FALSE, &camera_matrix[0][0]);; // View

		glm::mat4 projection_matrix = glm::perspective(45.0f, 1024.0f / 1024.0f, 1.0f, 100.0f);  // Projection
		glUniformMatrix4fv(location3, 1, GL_FALSE, &projection_matrix[0][0]);

		glDrawArrays(GL_QUADS, 0, 16);
		*/

		glfwSwapBuffers(window->GetWindowHandle());
		
	}
}