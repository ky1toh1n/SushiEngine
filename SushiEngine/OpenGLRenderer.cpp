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

		///Set view port size
		//glViewport(0, 0, 400, 600);

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
		

		/* Ali's Way

		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "triangles.vert" },
			{ GL_FRAGMENT_SHADER, "triangles.frag" },
			{ GL_NONE, NULL }
		};

		program = LoadShaders(shaders);
		glUseProgram(program);	//My Pipeline is set up

		*/

		
		const GLuint numVerts = 16;
		GLfloat cubeVerts[numVerts][3] = {
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

		// Creatint texture
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


		glGenTextures(100, texture);
		//glBindTexture(GL_TEXTURE_2D, texture[1]);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, textureData);
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


		// ----------------------------------------- TEXTURE TESTS -----------------------------------------------------

		ilInit();

		GLint width, height;
		// unsigned char* image = SOIL_load_image("apple.png", &width, &height, 0, SOIL_LOAD_RGB);

		// SuTexture* wall = new SuTexture();
		// wall->loadTextureFromFile("wall.png");

		std::string path = "wall.png";

		//Texture loading success
		bool textureLoaded = false;

		//Generate and set current image ID
		ILuint imgID = 0;
		ilGenImages(1, &imgID);
		ilBindImage(imgID);

		//Load image
		ILboolean success = ilLoadImage(path.c_str());

		//Image loaded successfully
		if (success == IL_TRUE)
		{
			printf("Success1??");
			//Convert image to RGBA
			success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);


			if (success == IL_TRUE)
			{
				printf("Success2??");
				//Create texture from file pixels
				//Bind texture ID
				glBindTexture(GL_TEXTURE_2D, texture[1]);

				//Generate texture
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLuint*)ilGetData());

				//Set texture parameters
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

				textureLoaded = true;
			}

			//Delete file from memory
			ilDeleteImages(1, &imgID);
		}

		//Report error
		if (!textureLoaded)
		{
			printf("Unable to load %s\n", path.c_str());
		}

		// ----------------------------------------- TEXTURE TESTS -----------------------------------------------------

		// Enable Depth Culling
		glEnable(GL_DEPTH_TEST);

		// Generate Ball Buffers and Send Data to GPU
		glGenBuffers(2, buffers);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts), cubeVerts, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertsColor), cubeVertsColor, GL_STATIC_DRAW);

		location = glGetUniformLocation(program, "model_matrix");
		location2 = glGetUniformLocation(program, "camera_matrix");
		location3 = glGetUniformLocation(program, "projection_matrix");


		glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoordinates), textureCoordinates, GL_STATIC_DRAW);
		glBindAttribLocation(program, 2, "vTexCoord");
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);
		
	}


	void OpenGLRenderer::render()
	{
		rotation += 0.005f;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Switch buffer binding point
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		// Set pointer to start of buffer attrib
		glEnableVertexAttribArray(0);
		// Describe how data is read
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glm::mat4 model_view = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 0));
		model_view = glm::rotate(model_view, rotation, glm::vec3(0.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(location, 1, GL_FALSE, &model_view[0][0]);

		glUniformMatrix4fv(location2, 1, GL_FALSE, &(camera->getMatrix())[0][0]); // View
		
		glm::mat4 projection_matrix = glm::perspective(45.0f, 1024.0f / 1024.0f, 1.0f, 100.0f);  // Projection
		glUniformMatrix4fv(location3, 1, GL_FALSE, &projection_matrix[0][0]);

		glDrawArrays(GL_QUADS, 0, 16);
		

		glfwSwapBuffers(window->GetWindowHandle());
		
	}
}