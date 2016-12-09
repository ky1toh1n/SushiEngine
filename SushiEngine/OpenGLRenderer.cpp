#include "OpenGLRenderer.h"

namespace SushiEngine
{
	OpenGLRenderer::OpenGLRenderer(Window* window) : AbstractRenderer(window)
	{
		Debug::LogConstructor("OpenGLRenderer", __FILENAME__, __LINE__);
		ModelManager::Init();
		init();
	}

	OpenGLRenderer::~OpenGLRenderer()
	{
		Debug::LogDeconstructor("OpenGLRenderer", __FILENAME__, __LINE__);
		glDetachShader(programID, vertexShaderID);
		glDetachShader(programID, fragmentShaderID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		glDeleteProgram(programID);
	}

	GLuint OpenGLRenderer::EZSHADING(SuShaderType pShaderType, const char * pFilePath, GLenum pGlShaderType, GLenum pShaderProgram)
	{
		//There's a tiny redundancy in SuShaderType and OpenGL's shader type. Not easy to fix atm.

		//Load shader into string
		ShaderLoader::loadShader(pShaderType, pFilePath);
		const char* adapter[1];
		adapter[0] = ShaderLoader::shader[pShaderType].c_str();

		//Compile and attach the shader to the programID
		GLuint shaderHandle = glCreateShader(pGlShaderType);
		glShaderSource(shaderHandle, 1, adapter, 0);
		glCompileShader(shaderHandle);
		glAttachShader(pShaderProgram, shaderHandle);

		return shaderHandle;
	}

	void OpenGLRenderer::init()
	{
		Debug::Log(EMessageType::S_INFO, "OpenGLRenderer::init", __FILENAME__, __LINE__);
		glewInit();

		/* Set up program and load shaders into it */
		programID = glCreateProgram();

		vertexShaderID = EZSHADING(SU_VERTEX_SHADER, "shaders/VertexShader.vert", GL_VERTEX_SHADER, programID);
		fragmentShaderID = EZSHADING(SU_FRAGMENT_SHADER, "shaders/FragmentShader.frag", GL_FRAGMENT_SHADER, programID);

		glLinkProgram(programID);
		glUseProgram(programID);	
		
		// Enable Depth Culling
		glEnable(GL_DEPTH_TEST);

		/* Get uniform locations */
		mModelLocation = glGetUniformLocation(programID, "model_matrix");
		mCameraLocation = glGetUniformLocation(programID, "camera_matrix");
		mProjectionLocation = glGetUniformLocation(programID, "projection_matrix");

		lightPositionUniformLocation = glGetUniformLocation(programID, "lightPosition");
		ambientUniformLocation = glGetUniformLocation(programID, "ambient_light");
		diffuseUniformLocation = glGetUniformLocation(programID, "diffuse_light");
	}
		// glClearColor(0.6, 0.6, 0.6, 1.0);


	void OpenGLRenderer::render(vector<SuGameObject*> gameObjects)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		vector<SuGameObject*>::iterator gameObject = gameObjects.begin();
		for (gameObject; gameObject != gameObjects.end(); ++gameObject)
		{
			DrawData data = ModelManager::getDrawData((*gameObject)->modelId);
			glBindBuffer(GL_ARRAY_BUFFER, *(*gameObject)->modelId);

			GLuint shaderPosition = glGetAttribLocation(programID, "vPosition");
			glEnableVertexAttribArray(shaderPosition);
			glVertexAttribPointer(shaderPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

			// Warning: for some reason glGetAttribLocation isnt returning the right value
			GLuint shaderColor = glGetAttribLocation(programID, "vColor");
			glDisableVertexAttribArray(shaderColor);

			// glBindAttribLocation(programID, 1, "vColor");
			if (data.hasColor)
			{
				glEnableVertexAttribArray(shaderColor);
				glVertexAttribPointer(shaderColor, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(vec3) * data.numVertices));
			}
			else
			{
				glEnableVertexAttribArray(shaderColor);
			}


			GLuint shaderUVs = glGetAttribLocation(programID, "vTexCoord");
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


			GLuint shaderNormals = glGetAttribLocation(programID, "vNormal");
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
			
			if (lightX <= -10)
			{
				goingright = true;
			}
			if (lightX >= 10)
			{
				goingright = false;
			}

			if (!goingright)
			{
				lightX -= 0.005f;
			}
			else
			{
				lightX += 0.005f;
			}


			vec4 lightPosition = vec4(lightX, 3.0f, 1.0f,0.0f);
			glUniform4fv(lightPositionUniformLocation, 1, &lightPosition[0]);

			vec4 ambientLight = vec4(0.2f, 0.2f, 0.2f, 1.0f);
			glUniform4fv(ambientUniformLocation, 1, &ambientLight[0]);

			vec4 diffuseLight = vec4(1.0f, 0.80f, 0.80f, 1.0f);
			glUniform4fv(diffuseUniformLocation, 1, &diffuseLight[0]);

			// ------------------- Model View Projection -------------------------
			// Temporary Position Setter
			Transform* t = (*gameObject)->GetComponent<Transform>();
			vec3 pos = *t->mPosition;
			vec3 rot = *t->mRotation;
			vec3 sca = *t->mScale;

			glm::mat4 model_view = glm::translate(glm::mat4(1.0), pos);

			// TODO: Use a matrix maybe?
			model_view = glm::rotate(model_view, rot.x, vec3(1.0f, 0.0f, 0.0f));
			model_view = glm::rotate(model_view, rot.y, vec3(0.0f, 1.0f, 0.0f));
			model_view = glm::rotate(model_view, rot.z, vec3(0.0f, 0.0f, 1.0f));
			// model_view *= glm::orientation(rot, vec3(0.0, 1.0, 0.0));
			model_view = glm::scale(model_view, sca);


			glUniformMatrix4fv(mModelLocation, 1, GL_FALSE, &model_view[0][0]);

			glUniformMatrix4fv(mCameraLocation, 1, GL_FALSE, &(mCamera->getMatrix())[0][0]); // View

			glm::mat4 projection_matrix = glm::perspective(45.0f, 1024.0f / 1024.0f, 1.0f, 100.0f);  // Projection
			glUniformMatrix4fv(mProjectionLocation, 1, GL_FALSE, &projection_matrix[0][0]);

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

		/* Swap that buffer */
		glfwSwapBuffers(mWindow->GetWindowHandle());
	}
}

