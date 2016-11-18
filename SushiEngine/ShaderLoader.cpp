#include "ShaderLoader.h"

namespace SushiEngine {

	std::string ShaderLoader::shader[NUM_SHADER_TYPES];

	ShaderLoader::ShaderLoader()
	{
	}


	ShaderLoader::~ShaderLoader()
	{
	}

	void ShaderLoader::loadShader(SuShaderType _type, const std::string _filepath)
	{
		shader[_type] = readFileToChar(_filepath);
	}

	std::string ShaderLoader::readFileToChar(const std::string _filepath)
	{
		std::ifstream file(_filepath); // strictly for reading files only

		if (!file.good())
		{
			Debug::Log(EMessageType::S_FATAL_ERROR, "Unable to find: " + _filepath + " ", __FILENAME__, __LINE__);
		}

		std::string data((std::istreambuf_iterator<char>(file)),
							std::istreambuf_iterator<char>());
		return data;
	}

}