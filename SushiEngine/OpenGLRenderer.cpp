#include "OpenGLRenderer.h"

namespace SushiEngine
{
	OpenGLRenderer::OpenGLRenderer(Window* window) : AbstractRenderer(window)
	{
		Debug::Log(EMessageType::S_INFO, "\tOpenGLRenderer()", __FILENAME__, __LINE__);
		ModelManager::Init();
		init();

	}


	OpenGLRenderer::~OpenGLRenderer()
	{
		Debug::Log(EMessageType::S_INFO, "\t~OpenGLRenderer()", __FILENAME__, __LINE__);
		glDetachShader(program, vertexShaderID);
		glDetachShader(program, fragmentShaderID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	void OpenGLRenderer::init()
	{
		Debug::Log(EMessageType::S_INFO, "\tOpenGLRenderer::init", __FILENAME__, __LINE__);
		glewInit();

		ShaderLoader::loadShader(SU_VERTEX_SHADER, "shaders/VertexShader.vert");
		ShaderLoader::loadShader(SU_FRAGMENT_SHADER, "shaders/FragmentShader.frag");

		// Testing Manual Loading of Shaders
		vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		const char* adapter[1];
		adapter[0] = ShaderLoader::shader[SU_VERTEX_SHADER].c_str();
		glShaderSource(vertexShaderID, 1, adapter, 0);
		adapter[0] = ShaderLoader::shader[SU_FRAGMENT_SHADER].c_str();
		glShaderSource(fragmentShaderID, 1, adapter, 0);

		glCompileShader(vertexShaderID);
		glCompileShader(fragmentShaderID);

		program = glCreateProgram();
		glAttachShader(program, vertexShaderID);
		glAttachShader(program, fragmentShaderID);

		glLinkProgram(program);
		glUseProgram(program);	// My Pipeline is set up
		
		// Enable Depth Culling
		glEnable(GL_DEPTH_TEST);

		location = glGetUniformLocation(program, "model_matrix");
		location2 = glGetUniformLocation(program, "camera_matrix");
		location3 = glGetUniformLocation(program, "projection_matrix");

		lightPositionUniformLocation = glGetUniformLocation(program, "lightPosition");
		ambientUniformLocation = glGetUniformLocation(program, "ambient_light");
		diffuseUniformLocation = glGetUniformLocation(program, "diffuse_light");


	}


	void OpenGLRenderer::render(vector<SuGameObject*> gameObjects)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		vector<SuGameObject*>::iterator gameObject = gameObjects.begin();
		for (gameObject; gameObject != gameObjects.end(); ++gameObject)
		{
			DrawData data = ModelManager::getDrawData((*gameObject)->modelId);
			glBindBuffer(GL_ARRAY_BUFFER, *(*gameObject)->modelId);

			GLuint shaderPosition = glGetAttribLocation(program, "vPosition");
			glEnableVertexAttribArray(shaderPosition);
			glVertexAttribPointer(shaderPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

			// Warning: for some reason glGetAttribLocation isnt returning the right value
			GLuint shaderColor = glGetAttribLocation(program, "vColor");
			glDisableVertexAttribArray(shaderColor);

			// glBindAttribLocation(program, 1, "vColor");
			if (data.hasColor)
			{
				glEnableVertexAttribArray(shaderColor);
				glVertexAttribPointer(shaderColor, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(vec3) * data.numVertices));
			}
			else
			{
				glEnableVertexAttribArray(shaderColor);
			}


			GLuint shaderUVs = glGetAttribLocation(program, "vTexCoord");
			if (data.hasTexture)
			{
				glEnableVertexAttribArray(shaderUVs);
				glVertexAttribPointer(shaderUVs, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(vec3) * data.numVertices * 2));
				glBindTexture(GL_TEXTURE_2D, *(*gameObject)->textureId);
			}
			else
			{
				glDisableVertexAttribArray(shaderUVs);
				glBindTexture(GL_TEXTURE_2D, NULL);
			}


			GLuint shaderNormals = glGetAttribLocation(program, "vNormal");
			if (data.hasNormals)
			{
				glEnableVertexAttribArray(shaderNormals);
				glVertexAttribPointer(shaderNormals, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(vec3) * data.numVertices));
			}
			else
			{
				glDisableVertexAttribArray(shaderNormals);

			}

			// ------------------- Lighting -------------------------

			vec4 lightPosition = vec4(0.0f, 10.0f, 2.0f,0.0f);
			glUniform4fv(lightPositionUniformLocation, 1, &lightPosition[0]);

			vec4 ambientLight = vec4(0.1f, 0.1f, 0.1f, 1.0f);
			glUniform4fv(ambientUniformLocation, 1, &ambientLight[0]);

			vec4 diffuseLight = vec4(1.0f, 0.80f, 0.80f, 1.0f);
			glUniform4fv(diffuseUniformLocation, 1, &diffuseLight[0]);

			// ------------------- Model View Projection -------------------------
			// Temporary Position Setter
			Transform* t = (*gameObject)->GetComponent<Transform>();
			vec3 pos = *t->mPosition;

			glm::mat4 model_view = glm::translate(glm::mat4(1.0), pos);
			model_view = glm::rotate(model_view, 0.0f, vec3(0.0f, 1.0f, 1.0f));
			glUniformMatrix4fv(location, 1, GL_FALSE, &model_view[0][0]);

			glUniformMatrix4fv(location2, 1, GL_FALSE, &(camera->getMatrix())[0][0]); // View

			glm::mat4 projection_matrix = glm::perspective(45.0f, 1024.0f / 1024.0f, 1.0f, 100.0f);  // Projection
			glUniformMatrix4fv(location3, 1, GL_FALSE, &projection_matrix[0][0]);

			// ------------------------------------------------------------------

			if (data.drawType == SU_LINES)
			{
				glDrawArrays(GL_LINES, 0, data.numVertices);
			}
			else
			{
				glDrawArrays(GL_TRIANGLES, 0, data.numVertices);
			}
		}

		glfwSwapBuffers(window->GetWindowHandle());
		
	}


}

