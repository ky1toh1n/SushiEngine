//// The ModelManager class handles the loading and management of external model files. This class ensures that only one instance of a model is loaded in gpy by keeping track of 
//// model Ids in the CPU
//
//#ifndef MODEL_MANAGER_H
//#define MODEL_MANAGER_H
//
//#include <map>
//#include <vector>
//#include <GL\glew.h>
//
//// typedef std::map<const std::string, GLuint> SuModelIDs;
//
//namespace SushiEngine
//{
//	struct DrawData
//	{
//
//	};
//
//	class ModelManager
//	{
//	public:
//		ModelManager();
//		~ModelManager();
//
//		ModelManager(const ModelManager&) = delete;
//		ModelManager(ModelManager&&) = delete;
//		ModelManager& operator=(const ModelManager&) = delete;
//		ModelManager& operator=(ModelManager&&) = delete;
//
//	private:
//		std::map<const std::string, GLuint*>* modelHandles;
//		std::vector<DrawData>* modelDrawData;
//
//		// Loads a model from a given path and returns an Id to that model once loaded in the GPU. If the model instance already exists,
//		// the function simply returns the Id to the model.
//		GLuint* loadModel(std::string _filepath);
//
//		// Removes the instance of the model in the GPU and also remove it from the list of loaded models
//		void destroyModel(GLuint* _id);
//
//		// Retrieves a struct that contains all neccessary attributes for a draw call
//		DrawData getDrawData(GLuint* _id);
//	};
//}
//#endif
//
//
