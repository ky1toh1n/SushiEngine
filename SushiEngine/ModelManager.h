// The ModelManager class handles the loading and management of external model files. This class ensures that only one instance of a model is loaded in GPU by keeping track of 
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
	enum DrawType
	{
		SU_LINES,
		SU_TRIANGLES
	};

	struct DrawData
	{
		unsigned int numVertices = 0;
		bool hasTexture = false;
		bool hasColor = false;
		bool hasNormals = false;
		DrawType drawType = SU_LINES;
		int bufferSize = -1;
		int positionBufferSize = -1;
		int colorBufferSize = -1;
		int uvBufferSize = -1;
		int normalBufferSize = -1;
	};

	class ModelManager
	{
	public:
		ModelManager() = delete;
		NO_COPY_CONSTRUCTORS(ModelManager)


		static bool Init();
		// Loads a model from a given path and returns an Id to that model once loaded in the GPU. If the model instance already exists,
		// the function simply returns the Id to the model.

		static const GLuint* LoadModel(const std::string _name, const GLfloat* _vertdata, const GLfloat* _coldata, const unsigned int numVerts);
		static const GLuint* LoadModel(std::string _filepath);

		// Retrieves a struct that contains all neccessary attributes for a draw call
		static DrawData getDrawData(const GLuint* _ID);

		static const GLuint* LoadTexture(std::string _filepath); // currently a member but can be changed later..?


	private:
		static map<const std::string, const GLuint> sModelHandles;
		static map<const std::string, const GLuint> sTextureHandles;
		static map<const GLuint, const DrawData> sModelDrawData;
		static Assimp::Importer sImporter;

		// Removes the instance of the model in the GPU and also remove it from the list of loaded models
		static void destroyModel(GLuint fID);

		// helper func: load and return the model data into memory
		static const aiScene* loadModelScene(std::string _filepath); 
	};
}
#endif