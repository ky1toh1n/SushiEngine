#include "ModelManager.h"

namespace SushiEngine 
{
	int ModelManager::verts = 0; // to be removed. see header
	map<const string, const GLuint> ModelManager::sModelHandles;
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

	const GLuint* ModelManager::LoadModel(string _filepath)
	{
		
		map<string, const GLuint>::iterator it;

		// Search for a filepath similar to _filepath
		it = sModelHandles.find(_filepath);
		
		// If found
		if (it != sModelHandles.end())
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

			vector<float> vertices;

			if (modelScene->HasMeshes())
			{
				cout << "# of Meshes: " << modelScene->mNumMeshes << endl;
				for (unsigned int m = 0; m < modelScene->mNumMeshes; m++)
				{
					const aiMesh* mesh = modelScene->mMeshes[m];
					cout << m+1 << ": # of Vertices: " << mesh->mNumVertices << endl;
					verts += mesh->mNumVertices;
					
					for (unsigned int v = 0; v < mesh->mNumVertices; v++)
					{
						aiVector3D* pPos = &mesh->mVertices[v];

						vertices.push_back(pPos->x);
						vertices.push_back(pPos->y);
						vertices.push_back(pPos->z);
					}
					//if (mesh->HasPositions())

				}
				cout << "total verts: " << verts << endl;
			}

			// Condition OK 
			GLuint buffer;

			glGenBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			// glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verts * 3, &vertices[0], GL_STATIC_DRAW); // The same thing as below
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * 3, &vertices[0], GL_STATIC_DRAW);

			//store the pointer inside modelHandles with the corresponding key
			sModelHandles.emplace(_filepath, buffer);
			GLuint test = sModelHandles[_filepath];
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

}