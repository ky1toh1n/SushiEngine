#include "ShaderLoader.h"

namespace SushiEngine {

	std::string ShaderLoader::shader[NUM_SHADER_TYPES];

	void ShaderLoader::loadShader(SuShaderType _type, const std::string _filepath)
	{
		shader[_type] = readFileToChar(_filepath);
	}

	// TODO: Change implementation -- apparently I'm not doing something right, or maybe a bad practice. Not sure what it is
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