#include "ModelManager.h"


namespace SushiEngine 
{

	int ModelManager::verts = 0;
	std::map<const std::string, const GLuint> ModelManager::modelHandles;
	std::vector<DrawData>* ModelManager::modelDrawData = nullptr;

	ModelManager::ModelManager()
	{
		Debug::Log(EMessageType::S_INFO, "ModelManager()", __FILENAME__, __LINE__);
	}


	ModelManager::~ModelManager()
	{
		Debug::Log(EMessageType::S_INFO, "~ModelManager()", __FILENAME__, __LINE__);
	}

	const GLuint* ModelManager::loadModel(std::string _filepath)
	{
		
		std::map<std::string, const GLuint>::iterator it;

		// Search for a filepath similar to _filepath
		it = modelHandles.find(_filepath);
		
		// If found
		if (it != modelHandles.end())
		{
			Debug::Log(EMessageType::S_INFO, "existing _filepath found" , __FILENAME__, __LINE__);
			cout << "exisiting _filepath found" << endl;
			// return the value of that key
			GLuint id = it->second;
			return (GLuint*)id;
		}

		
		
		else
		{
			// otherwise,
			Debug::Log(EMessageType::S_INFO, "exisiting _filepath not found", __FILENAME__, __LINE__);
			cout << "exisiting _filepath not found" << endl;

			// load the model from the filepath
			const aiScene* modelScene = loadModelScene(_filepath);

			if (!modelScene)
			{
				cout << "failed to load model into CPU" << endl;
				return nullptr;
			}
			else
			{
				cout << "model loaded into CPU" << endl;
			}


			
	
			// Test 1
			/*
			// Load data into the gpu via vbo
			if (modelScene->HasMeshes())
			{	// for every mesh in the model
				cout << "model has meshes: yes" << endl;
				cout << "meshes found: " << std::to_string(modelScene->mNumMeshes) << endl;
				// ;
				for (int m = 0; m < modelScene->mNumMeshes; m++)
				{	// for every vertex in each of those models
					cout << "Mesh# "<< m << endl;
					aiMesh* currentMesh = modelScene->mMeshes[m];
					cout << "Faces Found: " << std::to_string(currentMesh->mNumFaces) << endl;
					cout << "Vertices Found: " << std::to_string(currentMesh->mNumVertices) << endl;
					cout << "are the faces triangles? Faces * 3 == verts? : " << currentMesh->mNumFaces * 3 * 3 << endl;
				}
			}


			// Test
			cout << "Test# 01: direct memcopy from file" << endl;
			aiMesh* currentMesh = modelScene->mMeshes[0];
			cout << "Source array size:" << sizeof(*currentMesh->mVertices) << ", " << sizeof(*currentMesh->mVertices) * 1223 * 3 << ", " << currentMesh->mVertices << endl;
			GLfloat vertices[1223];
			memcpy(&vertices, &currentMesh->mVertices, sizeof(vertices));

			verts = currentMesh->mNumVertices;
			*/

			// Test 2
			/*
			std::vector<vec3> vertices;

			for (int m = 0; m < modelScene->mNumMeshes; m++)
			{
				const aiMesh* mesh = modelScene->mMeshes[m];
				for (unsigned int v = 0; v < mesh->mNumVertices; v++)
				{
					verts++;
					const aiVector3D* tmpPos = &(mesh->mVertices[v]);
					const aiVector3D* tmpNormal = &(mesh->mNormals[v]);

					vec3 vPos = vec3(tmpPos->x, tmpPos->y, tmpPos->z);
					vertices.push_back(vPos);
					// vec3 vNormal = vec3(tmpNormal->x, tmpNormal->y, tmpNormal->z);
					// vertices.push_back(vNormal);
				}
			}


			std::vector<GLfloat> indices;
			*/

			// Final Test before I give up

			// ------------------------------------------------------------------
			/*
			if (modelScene->HasMeshes())
			{
				cout << "# of Meshes: " << modelScene->mNumMeshes;
				for (unsigned int m = 0; m < modelScene->mNumMeshes; m++)
				{
					const aiMesh* mesh = modelScene->mMeshes[m];

					if (mesh->HasPositions())
					{
						float* vertices = new float[mesh->mNumVertices * 3];
						unsigned int elementCount = mesh->mNumFaces * 3;

						for (int i = 0; i < mesh->mNumVertices; ++i)
						{
							vertices[i * 3] = mesh->mVertices[i].x;
							vertices[i * 3 + 1] = mesh->mVertices[i].y;
							vertices[i * 3 + 2] = mesh->mVertices[i].z;
						}
					}
				}
			}
			*/
			// ------------------------------------------------------------------


			return nullptr;

			// Condition OK 
			GLuint buffer;

			glGenBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			//cout << "Sending Data to GPU..." << sizeof(vertices) << ", " << sizeof(vertices) * 1223 << endl;
			//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

			//store the pointer inside modelHandles with the corresponding key
			modelHandles.emplace(_filepath, buffer);
			GLuint test = modelHandles[_filepath];
			// cout << test << endl;
			// lastly, return the pointer to the model
			return &modelHandles[_filepath];
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
		std::map<std::string, const GLuint>::iterator it;
		// find the id in the list
		for (it = modelHandles.begin(); it != modelHandles.end(); ++it)
		{
			// if found
			if (it->second == _id)
			{
				// delete it from the list
				modelHandles.erase(it);
				break;
			}
		}
	}


	// Condition OK
	const aiScene* ModelManager::loadModelScene(std::string _filepath)
	{
		Assimp::Importer importer;
		const aiScene* modelScene;

		std::ifstream fileIn(_filepath.c_str());

		if (fileIn.fail())
		{
			Debug::Log(EMessageType::S_ERROR, "Failed to open file : " + (std::string)_filepath.c_str(), __FILENAME__, __LINE__);
			return nullptr;
		}


		// modelScene = importer.ReadFile(_filepath, aiProcessPreset_TargetRealtime_Quality);
		modelScene = importer.ReadFile(_filepath,
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);

		if (!modelScene)
		{
			Debug::Log(EMessageType::S_ERROR, importer.GetErrorString(), __FILENAME__, __LINE__);
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

}