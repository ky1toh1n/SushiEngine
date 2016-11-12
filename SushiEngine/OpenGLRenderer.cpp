/*
Nicco NTS:

Window -> New Vertical Tab Group

and

View -> Task List.. to view TODOs

*/


#include "OpenGLRenderer.h"

namespace SushiEngine {

	OpenGLRenderer::OpenGLRenderer(Window* window) : AbstractRenderer(window)
	{
		init();
	}


	OpenGLRenderer::~OpenGLRenderer()
	{
		glDetachShader(program, vertexShaderID);
		glDetachShader(program, fragmentShaderID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	void OpenGLRenderer::init() {

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
		
		const GLuint numVerts = 16;
		const GLfloat cubeVerts[numVerts][3] = {
			{ -0.5, +0.5, -0.5 }, // B
			{ +0.5, +0.5, -0.5 },
			{ +0.5, -0.5, -0.5 },
			{ -0.5, -0.5, -0.5 },

			{ -0.5, +0.5, +0.5 }, // F
			{ +0.5, +0.5, +0.5 },
			{ +0.5, -0.5, +0.5 },
			{ -0.5, -0.5, +0.5 },

			{ +0.5, +0.5, +0.5 }, // R
			{ +0.5, +0.5, -0.5 },
			{ +0.5, -0.5, -0.5 },
			{ +0.5, -0.5, +0.5 },

			{ -0.5, +0.5, +0.5 }, // L
			{ -0.5, +0.5, -0.5 },
			{ -0.5, -0.5, -0.5 },
			{ -0.5, -0.5, +0.5 },
		};

		const GLfloat cubeVertsColor[numVerts][3] = {
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

		GLfloat textureData[] = {
			1.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 0.0f
		};

		GLfloat textureCoordinates[numVerts][2] = {
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,

			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f
		};

		// Enable Depth Culling
		glEnable(GL_DEPTH_TEST);

		// -----------------------------------------SUMESH TESTS --------------------------------------------------------
		
		mesh = new SuMesh2();
		bool meshTest = mesh->LoadMesh(cubeVerts[0], cubeVertsColor[0], numVerts);
		if (meshTest) printf("Mesh Test Load -- OK\n");

		// -----------------------------------------SUMESH TESTS END-----------------------------------------------------
		// ---------------------------------------- SUTEXTURE TESTS -----------------------------------------------------

		ilInit();

		// WARNING: unused local variable
		//GLint width, height;
		std::string path = "wall.png";

		//Generate and set current image ID
		ILuint imgID = 0;
		ilGenImages(1, &imgID);
		ilBindImage(imgID);

		//Load image
		ILboolean success = ilLoadImage(path.c_str());
		if (success) printf("DevIL Load Image -- OK\n");

		tex = new SuTexture();
		bool texTest = tex->LoadTexture((GLuint*)ilGetData(), textureCoordinates[0], (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT));
		std::cout << (GLuint)ilGetInteger(IL_IMAGE_WIDTH) << "x" << (GLuint)ilGetInteger(IL_IMAGE_HEIGHT)<<std::endl;
		if (meshTest) printf("Texture Test Load -- OK\n");

		ilDeleteImages(1, &imgID);

		// ---------------------------------------- SUTEXTURE TESTS END--------------------------------------------------
		// ---------------------------------------- SUGAMEOBJECT TESTS --------------------------------------------------

		go = new SuGameObject(glm::vec4(0, 0, 0, 1));
		go->mesh = mesh; // temporary setters
		go->texture = tex;

		if (go) printf("Game Object Creation -- OK\n");
		// ---------------------------------------- SUGAMEOBJECT END ----------------------------------------------------

		// ---------------------------------------- ASSIMP TESTS --------------------------------------------------

		// TODO: ModelLoader / Resourcemanager

		const aiScene* scene;
		Assimp::Importer importer;

		std::string filename = "models/ananas.fbx";
		std::ifstream fileIn(filename.c_str());
		if (fileIn.fail())
		{
			//std::cout << "failed to open file " << filename.c_str() << std::endl;
			Debug::Log(EMessageType::S_ERROR, "Failed to open file : " + (std::string)filename.c_str(), __FILENAME__, __LINE__);

		}
		else
		{
			printf("Opening .fbx file -- OK\n");
			fileIn.close();
		}

		scene = importer.ReadFile(filename, aiProcessPreset_TargetRealtime_Quality);

		if (!scene)
		{
			//std::cout << importer.GetErrorString() << std::endl;
			Debug::Log(EMessageType::S_ERROR, importer.GetErrorString(), __FILENAME__, __LINE__);

		}
		else {
			printf("Asset Loading -- OK\n");
		}

		// ---------------------------------------- ASSIMP TESTS END ----------------------------------------------------


		location = glGetUniformLocation(program, "model_matrix");
		location2 = glGetUniformLocation(program, "camera_matrix");
		location3 = glGetUniformLocation(program, "projection_matrix");

		
	}


	void OpenGLRenderer::render()
	{
		rotation += 0.005f;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUniformMatrix4fv(location2, 1, GL_FALSE, &(camera->getMatrix())[0][0]); // View

		glm::mat4 projection_matrix = glm::perspective(45.0f, 1024.0f / 1024.0f, 1.0f, 100.0f);  // Projection
		glUniformMatrix4fv(location3, 1, GL_FALSE, &projection_matrix[0][0]);

		//----- Manual Update of Position

		glm::mat4 model_view = glm::translate(glm::mat4(1.0), go->position);
		model_view = glm::rotate(model_view, rotation, glm::vec3(0.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(location, 1, GL_FALSE, &model_view[0][0]);

		go->Render();

		glfwSwapBuffers(window->GetWindowHandle());
		
	}
}

