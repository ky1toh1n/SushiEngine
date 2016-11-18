#include "ModelManager.h"

namespace SushiEngine 
{
	int ModelManager::verts = 0; // to be removed. see header
	map<const std::string, const GLuint> ModelManager::sModelHandles;
	map<const std::string, const GLuint> ModelManager::sTextureHandles;
	Assimp::Importer ModelManager::sImporter;

	// std::vector<DrawData>* ModelManager::modelDrawData = nullptr;

	ModelManager::ModelManager()
	{
		Debug::Log(EMessageType::S_INFO, "ModelManager()", __FILENAME__, __LINE__);
	}


	ModelManager::~ModelManager()
	{
		Debug::Log(EMessageType::S_INFO, "~ModelManager()", __FILENAME__, __LINE__);
	}

	bool ModelManager::Init()
	{
		ilInit();
		return true;
	}

	const GLuint* ModelManager::LoadModel(std::string _filepath)
	{
		
		map<string, const GLuint>::iterator it;

		// Search for a filepath similar to _filepath
		it = sModelHandles.find(_filepath);
		
		// If found
		if (it != sModelHandles.end())
		{
			Debug::Log(EMessageType::S_INFO, "existing _filepath found" , __FILENAME__, __LINE__);
			// cout << "exisiting _filepath found" << endl;
			// return the value of that key
			GLuint id = it->second;
			return (GLuint*)id;
		}
		else
		{
			// otherwise,
			Debug::Log(EMessageType::S_INFO, "exisiting _filepath not found", __FILENAME__, __LINE__);
			// cout << "exisiting _filepath not found" << endl;

			// load the model from the filepath
			const aiScene* modelScene = loadModelScene(_filepath);

			if (!modelScene)
			{
				cout << "failed to load model into CPU" << endl;
				return nullptr;
			}
			else
			{
				// cout << "model loaded into CPU" << endl;
			}

			vector<vec3> vertexPositions;
			vector<vec3> vertexNormals;
			vector<vec2> vertexUVs;

			if (modelScene->HasMeshes())
			{
				// cout << "# of Meshes: " << modelScene->mNumMeshes << endl;
				for (unsigned int m = 0; m < modelScene->mNumMeshes; m++)
				{
					const aiMesh* mesh = modelScene->mMeshes[m];
					verts += mesh->mNumVertices;
					// cout << m + 1 << ": # of Vertices: " << mesh->mNumVertices << endl;

					
					for (unsigned int v = 0; v < mesh->mNumVertices; v++)
					{
						aiVector3D* pPos = &mesh->mVertices[v];
						aiVector3D* pNor = &mesh->mNormals[v];

						vec3 vPos = vec3(pPos->x, pPos->y, pPos->z);
						vec3 vNor = vec3(pNor->x, pNor->y, pNor->z);

						vertexPositions.push_back(vPos);
						vertexNormals.push_back(vNor);

						if (mesh->HasTextureCoords(0))
						{
							aiVector3D* pUV = &mesh->mTextureCoords[0][v];
							vec2 vUV = vec2(pUV->x, pUV->y);
							vertexUVs.push_back(vUV);
							// if (v < 1) cout << "			sample vTexCoord: (" << pUV->x << "," << pUV->y << ")" << endl;
						}

					}
					//if (mesh->HasPositions())

				}
				// cout << "total verts: " << verts << endl;
				// printf("# Textures: %i\n", modelScene->mNumTextures);
				// printf("# Materials: %i\n", modelScene->mNumMaterials);
				if (modelScene->HasTextures())
				{
				}

				if (modelScene->HasMaterials())
				{
					//for (int mat = 0; mat < modelScene->mNumMaterials; mat++)
				}

			}

			// Condition: being improved
			GLuint buffer;

			glGenBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			// glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verts * 3, &vertices[0], GL_STATIC_DRAW); // The same thing as below
			// glBufferData(GL_ARRAY_BUFFER, vertices.size() * 3, &vertices[0], GL_STATIC_DRAW);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * verts  + sizeof(vec2) * verts, NULL, GL_STATIC_DRAW); // allocate buffer memory for the actual size of vertices container
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3) * verts, &vertexPositions[0]);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec3) * verts, sizeof(vec2) * verts, &vertexUVs[0]);
			// glBufferSubData(GL_VERTEX_ARRAY, sizeof(vec3), sizeof(vec3) * verts, &vertices[0].vNormal);

			// Memory Tests
			/*
			printf("-------------------------------\n");
			printf("sizeof(vertexPositions): %u\n", sizeof(vertexPositions));
			printf("sizeof(vec3): %u\n", sizeof(vec3));
			printf("sizeof(float) * 3: %u\n", sizeof(float) * 3);
			printf("-------------------------------\n");
			printf("&vertices: %u\n", &vertexPositions);
			printf("&vertices[0]: %u\n", &vertexPositions[0]);
			printf("&vertexPositions: %u\n", &vertexPositions[0]);
			printf("&vertexNormals %u\n", &vertexNormals[0]);
			printf("&vertexUVs %u\n", &vertexUVs[0]);
			printf("&vertexPositions[1]: %u\n", &vertexPositions[1]);
			printf("-------------------------------\n");
			*/

			//store the pointer inside modelHandles with the corresponding key
			sModelHandles.emplace(_filepath, buffer);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// lastly, return the pointer to the model
			// TODO: make this more efficient by just returning the buffer.. im just not sure how its gonna work if i return it locally
			return &sModelHandles[_filepath];
		}
	}

	// Untested
	void ModelManager::destroyModel(GLuint _id)
	{
		
		/// Remove from the GPU
		// if the id is a vbo
		if (glIsBuffer(_id))
		{
			// delete from gpu
			glDeleteBuffers(1, &_id);
		}

		/// Remove from the list of instances
		map<string, const GLuint>::iterator it;
		// find the id in the list
		for (it = sModelHandles.begin(); it != sModelHandles.end(); ++it)
		{
			// if found
			if (it->second == _id)
			{
				// delete it from the list
				sModelHandles.erase(it);
				break;
			}
		}
	}


	// Condition OK
	const aiScene* ModelManager::loadModelScene(std::string _filepath)
	{

		const aiScene* modelScene;

		ifstream fileIn(_filepath.c_str());

		if (fileIn.fail())
		{
			Debug::Log(EMessageType::S_ERROR, "Failed to open file : " + (std::string)_filepath.c_str(), __FILENAME__, __LINE__);
			return nullptr;
		}

		// modelScene = importer.ReadFile(_filepath, aiProcessPreset_TargetRealtime_Quality);
		modelScene = sImporter.ReadFile(_filepath,
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			// aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);

		if (!modelScene)
		{
			Debug::Log(EMessageType::S_ERROR, sImporter.GetErrorString(), __FILENAME__, __LINE__);
		}
		else
		{
			Debug::Log(EMessageType::S_ERROR, "ModelManager::loadModelScene() SUCCESS ", __FILENAME__, __LINE__);
		}

		return modelScene;
	}

	//DrawData ModelManager::getDrawData(const GLuint* _id)
	//{
	//}

	const GLuint* ModelManager::LoadTexture(std::string _filepath)
	{

		map<string, const GLuint>::iterator it;

		// Search for a filepath similar to _filepath
		it = sTextureHandles.find(_filepath);
		if (it != sTextureHandles.end())
		{
			GLuint id = it->second;
			return (GLuint*)id;
		}
		else
		{

			//Generate and set current image ID
			ILuint imgID = 0;
			ilGenImages(1, &imgID);
			ilBindImage(imgID);

			//Load image
			ILboolean success = ilLoadImage(_filepath.c_str());
			if (success) 
			{
				// printf("DevIL Load Image -- OK\n");
			}
			else
			{
				Debug::Log(EMessageType::S_ERROR, "ModelManager::LoadTexture() FILEPATH NOT FOUND", __FILENAME__, __LINE__);
				return nullptr;
			}

			//  OPEN GL STUFF-----------------------


			GLuint mTextureID;
			glGenTextures(1, &mTextureID);
			glBindTexture(GL_TEXTURE_2D, mTextureID);

			//Generate texture
			// glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLuint*)ilGetData());

			//Set texture parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


			sTextureHandles.emplace(_filepath, mTextureID);

			// -----------------------------------


			// cout << (GLuint)ilGetInteger(IL_IMAGE_WIDTH) << "x" << (GLuint)ilGetInteger(IL_IMAGE_HEIGHT) << endl;

			ilDeleteImages(1, &imgID);

			// lastly, return the pointer to the image
			// cout << sTextureHandles[_filepath] << endl;

			glBindTexture(GL_TEXTURE_2D, 0);



			return &sTextureHandles[_filepath];
		}
	}
}