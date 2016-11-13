#include "ModelManager.h"


namespace SushiEngine 
{

	ModelManager::ModelManager()
	{
	}


	ModelManager::~ModelManager()
	{
	}

	GLuint* ModelManager::loadModel(std::string _filepath)
	{
		std::map<std::string, GLuint*>::iterator it;

		// Search for a filepath similar to _filepath
		it = modelHandles->find(_filepath);

		// If found
		if (it != modelHandles->end())
		{
			// return the value of that key
			return it->second;
		}
		else 
		{
			// otherwise, create a buffer object reference pointer

			// load data into the gpu via vbo

			// store the pointer inside modelHandles with the corresponding key

			// lastly, return the pointer to the model
			
		}
	}

	void ModelManager::destroyModel(GLuint* id)
	{

		/// Remove from the GPU
		// if the id is a vbo
		if (glIsBuffer(*id))
		{
			// delete from gpu
			glDeleteBuffers(1, id);
		}

		/// Remove from the list of instances
		std::map<std::string, GLuint*>::iterator it;
		// find the id in the list
		for (it = modelHandles->begin(); it != modelHandles->end(); ++it)
		{
			// if found
			if (it->second == id)
			{
				// delete it from the list
				modelHandles->erase(it);
				break;
			}
		}
	}

	DrawData ModelManager::getDrawData(GLuint* _id)
	{
	}

}