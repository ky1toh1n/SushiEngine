// The ModelManager class handles the loading and management of external model files. This class ensures that only one instance of a model is loaded in gpy by keeping track of 
// model Ids in the CPU

#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <GL\glew.h>
#include "IL\il.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include "Debug.h"
#include "Macros.h"
#include "SuGameObject.h"

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

		NO_COPY_CONSTRUCTORS(ModelManager)

		// Loads a model from a given path and returns an Id to that model once loaded in the GPU. If the model instance already exists,
		// the function simply returns the Id to the model.
		static const GLuint* LoadModel(std::string fFilepath);

		// Retrieves a struct that contains all neccessary attributes for a draw call
		//static DrawData getDrawData(const GLuint* fID);

		// Test ModelImporter

		static int verts; // TODO: replace this for something more dynamic

	private:
		static map<const std::string, const GLuint> sModelHandles;
		static vector<DrawData>* sModelDrawData;
		const aiScene* mModelScene;
		static Assimp::Importer sImporter;

		// Removes the instance of the model in the GPU and also remove it from the list of loaded models
		static void destroyModel(GLuint fID);

		// helper func: load and return the model data into memory
		static const aiScene* loadModelScene(string fFilepath); 
	};
}
#endif


