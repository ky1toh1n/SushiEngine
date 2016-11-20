#include "ModelManager.h"

namespace SushiEngine 
{
	int ModelManager::verts = 0; // to be removed. see header
	map<const std::string, const GLuint> ModelManager::sModelHandles;
	map<const std::string, const GLuint> ModelManager::sTextureHandles;
	map<const GLuint, const DrawData> ModelManager::sModelDrawData;
	Assimp::Importer ModelManager::sImporter;


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

	// TODO: simplify container checks???
	const GLuint* ModelManager::LoadModel(const std::string _name, const GLfloat* _vertdata, const GLfloat* _coldata,  const unsigned int _numVerts)
	{

		DrawData drawData;
		drawData.numVertices = _numVerts;
		drawData.hasColor = true;
		map<string, const GLuint>::iterator it;

		// Search for a filepath similar to _filepath
		it = sModelHandles.find(_name);

		if (it != sModelHandles.end())
		{
			Debug::Log(EMessageType::S_INFO, "existing _filepath found", __FILENAME__, __LINE__);
			// cout << "exisiting _filepath found" << endl;
			// return the value of that key
			GLuint id = it->second;
			return (GLuint*)id;
		}
		else
		{
			GLuint buffer;
			glGenBuffers(1, &buffer);

			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * _numVerts * 2, NULL, GL_STATIC_DRAW);

			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3) * _numVerts, _vertdata);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec3) * _numVerts, sizeof(vec3) * _numVerts, _coldata);

			sModelHandles.emplace(_name, buffer);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			sModelDrawData.emplace(buffer, drawData);
			return &sModelHandles[_name];
		}
	}

	const GLuint* ModelManager::LoadModel(std::string _filepath)
	{
		
		map<string, const GLuint>::iterator it;
		unsigned int numVerts = 0;
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

			DrawData drawData;
			vector<vec3> vertexPositions;
			vector<vec3> vertexNormals;
			vector<vec2> vertexUVs;

			if (modelScene->HasMeshes())
			{
				// cout << "# of Meshes: " << modelScene->mNumMeshes << endl;
				for (unsigned int m = 0; m < modelScene->mNumMeshes; m++)
				{
					const aiMesh* mesh = modelScene->mMeshes[m];
					numVerts += mesh->mNumVertices;
					// cout << m + 1 << ": # of Vertices: " << mesh->mNumVertices << endl;

					for (unsigned int v = 0; v < mesh->mNumVertices; v++)
					{

						if (mesh->HasPositions())
						{
							aiVector3D* pPos = &mesh->mVertices[v];
							vec3 vPos = vec3(pPos->x, pPos->y, pPos->z);
							vertexPositions.push_back(vPos);
						}

						if (mesh->HasNormals())
						{
							aiVector3D* pNor = &mesh->mNormals[v];
							vec3 vNor = vec3(pNor->x, pNor->y, pNor->z);
							vertexNormals.push_back(vNor);
						}


						if (mesh->HasTextureCoords(0))
						{
							aiVector3D* pUV = &mesh->mTextureCoords[0][v];
							vec2 vUV = vec2(pUV->x, pUV->y);
							vertexUVs.push_back(vUV);
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

			glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * numVerts * 2 + sizeof(vec2) * numVerts, NULL, GL_STATIC_DRAW); // allocate buffer memory for the actual size of vertices container
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3) * numVerts, &vertexPositions[0]);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec3) * numVerts, sizeof(vec3) * numVerts, &vertexNormals[0]);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec3) * numVerts * 2, sizeof(vec2) * numVerts, &vertexUVs[0]);

			//store the pointer inside modelHandles with the corresponding key
			sModelHandles.emplace(_filepath, buffer);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			drawData.numVertices = numVerts;
			drawData.hasTexture = true;
			drawData.drawType = SU_TRIANGLES;
			drawData.hasNormals = true;

			sModelDrawData.emplace(buffer, drawData);

			// lastly, return the pointer to the model
			// TODO: make this more efficient by just returning the buffer.. im just not sure how its gonna work if i return it locally
			return &sModelHandles[_filepath];
		}
	}

	DrawData ModelManager::getDrawData(const GLuint* _id)
	{
		map<const GLuint, const DrawData>::iterator it;

		it = sModelDrawData.find(*_id);
		if (it != sModelDrawData.end())
		{
			DrawData drawData = it->second;
			return drawData;
		}
		return sModelDrawData[*_id];
	}

	// Untested
	void ModelManager::destroyModel(GLuint fID)
	{
		/// Remove from the GPU
		// if the id is a vbo
		if (glIsBuffer(fID))
		{
			// delete from gpu
			glDeleteBuffers(1, &fID);
		}

		/// Remove from the list of instances
		map<string, const GLuint>::iterator it;
		// find the id in the list
		for (it = sModelHandles.begin(); it != sModelHandles.end(); ++it)
		{
			// if found
			if (it->second == fID)
			{
				// delete it from the list
				sModelHandles.erase(it);
				break;
			}
		}
	}


	// Condition OK
	const aiScene* ModelManager::loadModelScene(std::string fFilepath)
	{

		const aiScene* modelScene;

		ifstream fileIn(fFilepath.c_str());

		if (fileIn.fail())
		{
			Debug::Log(EMessageType::S_ERROR, "Failed to open file : " + (std::string)fFilepath.c_str(), __FILENAME__, __LINE__);
			return nullptr;
		}

		// modelScene = importer.ReadFile(_filepath, aiProcessPreset_TargetRealtime_Quality);
		modelScene = sImporter.ReadFile(fFilepath,
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