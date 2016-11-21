/** Handles the loading of models (and textures) into the GPU.
* Ensures that there a unique model is only loaded once.
*/
#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H
/* Third Party */
#include <GL\glew.h>
#include "IL\il.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
/* SushiEngine */
#include "Debug.h"
#include "Macros.h"
#include "SuGameObject.h"
/* ---- */
namespace SushiEngine
{
	enum DrawType
	{
		SU_LINES,
		SU_TRIANGLES
	};
	/* ---- */
	struct DrawData
	{
		unsigned int numVertices = 0;
		bool hasTexture = false;
		bool hasColor = false;
		DrawType drawType = SU_LINES;
	};
	/* ---- */
	class ModelManager
	{
	public:
		/* Constructor */
		NO_COPY_CONSTRUCTORS(ModelManager)

		/* Static fields */
		static int verts; // TODO: replace this with something more dynamic

		/* Static methods */
		static bool Init();

		// Loads a model from a given path and returns an Id to that model once loaded in the GPU. If the model instance already exists,
		// the function simply returns the Id to the model.
		static const GLuint* LoadModel(const std::string _name, const GLfloat* _vertdata, const GLfloat* _coldata, const unsigned int numVerts);
		static const GLuint* LoadModel(std::string _filepath);

		// Retrieves a struct that contains all neccessary attributes for a draw call
		static DrawData getDrawData(const GLuint* _ID);

		// Test ModelImporter
		static const GLuint* LoadTexture(std::string _filepath); // currently a member but can be changed later..?
	private:
		/* Constructor */
		ModelManager();
		~ModelManager();

		/* Static fields */
		static map<const std::string, const GLuint> sModelHandles;
		static map<const std::string, const GLuint> sTextureHandles;
		static map<const GLuint, const DrawData> sModelDrawData;
		static Assimp::Importer sImporter;

		/* Static methods */
		// Removes the instance of the model in the GPU and also remove it from the list of loaded models
		static void destroyModel(GLuint fID);

		// helper func: load and return the model data into memory
		static const aiScene* loadModelScene(std::string _filepath);
	};
}
#endif