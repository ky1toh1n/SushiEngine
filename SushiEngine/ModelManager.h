// The ModelManager class handles the loading and management of external model files. This class ensures that only one instance of a model is loaded in gpy by keeping track of 
// model Ids in the CPU

#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include "Debug.h"
#include "Macros.h"
#include <map>
#include <vector>
#include <GL\glew.h>
#include "IL\il.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
// typedef std::map<const std::string, GLuint> SuModelIDs;

namespace SushiEngine
{
	struct DrawData
	{

	};

	class ModelManager
	{
	public:
		ModelManager();
		~ModelManager();

		ModelManager(const ModelManager&) = delete;
		ModelManager(ModelManager&&) = delete;
		ModelManager& operator=(const ModelManager&) = delete;
		ModelManager& operator=(ModelManager&&) = delete;


		// Loads a model from a given path and returns an Id to that model once loaded in the GPU. If the model instance already exists,
		// the function simply returns the Id to the model.
		static const GLuint* loadModel(std::string _filepath);

		// Retrieves a struct that contains all neccessary attributes for a draw call
		static DrawData getDrawData(const GLuint* _id);

		// Test ModelImporter

		static int verts;


	private:
		static std::map<const std::string, const GLuint> modelHandles;
		static std::vector<DrawData>* modelDrawData;
		const aiScene* modelScene;



		// Removes the instance of the model in the GPU and also remove it from the list of loaded models
		void destroyModel(GLuint _id);


		// helper func: load and return the model data into memory
		static const aiScene* loadModelScene(std::string _filepath); 



	};
}
#endif


