#include "ModelManager.h"


namespace SushiEngine 
{

	ModelManager::ModelManager()
	{
		modelHandles = new std::map<std::string, GLuint>;
	}


	ModelManager::~ModelManager()
	{
	}

	GLuint ModelManager::loadModel(std::string filepath)
	{

	}

}