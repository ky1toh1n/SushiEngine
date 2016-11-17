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


		// Testing Manual Loading of Shaders
		vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

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
		
		// Enable Depth Culling
		glEnable(GL_DEPTH_TEST);

		location = glGetUniformLocation(program, "model_matrix");
		location2 = glGetUniformLocation(program, "camera_matrix");
		location3 = glGetUniformLocation(program, "projection_matrix");

		// ModelImporter Tests


		// camera->translate(0.0f, 0.5f); // Dont use yet till fixed

		go = new SuGameObject(glm::vec3(0,0,0));
		if (!go) cout << "Failed to create GameObject" << endl;
		//go->modelId = ModelManager::LoadModel("models/Wooden_House/Wooden_House.fbx");
		// go->modelId = ModelManager::LoadModel("models/cube.obj");
		// go->modelId = ModelManager::LoadModel("models/ananas.fbx");
		// go->modelId = ModelManager::LoadModel("models/Crate/Crate1.3ds");
		go->modelId = ModelManager::LoadModel("models/house/house.obj");
		if (!go->modelId)
		{
			cout << "Failed to set GameObject's model" << endl;
		}
		else
		{


		}

		go->textureId = ModelManager::LoadTexture("models/house/house2.png");
		// go->textureId = ModelManager::LoadTexture("models/Wooden_House/texhouse2.png");
		// go->textureId = ModelManager::LoadTexture("models/Wooden_House/texhouse.png");
		// go->textureId = ModelManager::LoadTexture("models/Crate/RTS_Crate.png");
	    // go->textureId = ModelManager::LoadTexture("models/Crate/crate_1.jpg");
		// go->textureId = ModelManager::LoadTexture("models/house/house.jpg");
		// go->textureId = ModelManager::LoadTexture("models/Wooden_House/House_Texture.png");
		// go->textureId = ModelManager::LoadTexture("models/Wooden_House/rsz_1house_texture_s.png");
		// go->textureId = ModelManager::LoadTexture("wall.png");
		if (!go->textureId)
		{
			cout << "Failed to set GameObject's texture" << endl;
		}
		else
		{


		}

		glBindBuffer(GL_ARRAY_BUFFER, *go->modelId);
		GLuint shaderPosition = glGetAttribLocation(program, "vPosition");
		cout << "posattrib loc: " << shaderPosition << endl;
		glEnableVertexAttribArray(shaderPosition);
		glVertexAttribPointer(shaderPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
		cout << "textureId: " << *go->textureId << endl;

		glBindTexture(GL_TEXTURE_2D, *go->textureId);
		GLuint shaderUVs = glGetAttribLocation(program, "vTexCoord");
		cout << "texcoordattrib loc: " << shaderUVs << endl;
		glEnableVertexAttribArray(shaderUVs);
		glVertexAttribPointer(shaderUVs, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(vec3) * ModelManager::verts));

	}


	void OpenGLRenderer::render()
	{
		rotation += 0.005f;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model_view = glm::translate(glm::mat4(1.0), vec3(0.0f, 0.0f, 0.0f));
		model_view = glm::rotate(model_view, rotation, vec3(0.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(location, 1, GL_FALSE, &model_view[0][0]);

		glUniformMatrix4fv(location2, 1, GL_FALSE, &(camera->getMatrix())[0][0]); // View

		glm::mat4 projection_matrix = glm::perspective(45.0f, 1024.0f / 1024.0f, 1.0f, 100.0f);  // Projection
		glUniformMatrix4fv(location3, 1, GL_FALSE, &projection_matrix[0][0]);


		// glDrawArrays(GL_LINE_STRIP, 0, ModelManager::verts);
		glDrawArrays(GL_TRIANGLES, 0, ModelManager::verts);

		glfwSwapBuffers(window->GetWindowHandle());
		
	}
}

