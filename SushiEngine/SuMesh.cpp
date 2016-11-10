#include "SuMesh.h"
#include <iostream>

namespace SushiEngine
{
	SuMesh::SuMesh(std::string filename)
	{
		if (ImportModel(filename))
		{
			std::cout << "imported model successfully" << std::endl;
		}
		else
		{
			std::cout << "model import failed" << std::endl;
		}
	}

	bool SuMesh::ImportModel(const std::string filename)
	{
		std::ifstream fileIn(filename.c_str());
		if (fileIn.fail())
		{
			//std::cout << "failed to open file " << filename.c_str() << std::endl;
			Debug::Log(EMessageType::S_ERROR, "Failed to open file : " + (std::string)filename.c_str(), __FILENAME__, __LINE__);
		}
		else
		{
			fileIn.close();
		}



		scene = importer.ReadFile(filename, aiProcessPreset_TargetRealtime_Quality);

		if (!scene)
		{
			//std::cout << importer.GetErrorString() << std::endl;
			Debug::Log(EMessageType::S_ERROR, importer.GetErrorString(), __FILENAME__, __LINE__);
			return false;
		}



		return true;
	}


	SuMesh::~SuMesh()
	{
	}
}