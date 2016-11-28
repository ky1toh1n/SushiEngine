/** A static class that handles shader loading externally, and maybe later on keep track of various mShaderId's used within the game */
#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H
/* System */
#include <fstream>
#include <string>
/* SushiEngine */
#include "Debug.h"
#include "Macros.h"
namespace SushiEngine {
	enum SuShaderType
	{
		SU_VERTEX_SHADER,
		SU_FRAGMENT_SHADER,
		NUM_SHADER_TYPES,
	};
	/* ---- */
	class ShaderLoader
	{
	public:
		/*Delete Constructors */
		ShaderLoader() = delete;
		NO_COPY_CONSTRUCTORS(ShaderLoader)

		/* Static fields */
		static std::string shader[NUM_SHADER_TYPES];

		/* Static methods */	
		static void loadShader(SuShaderType _type, const std::string _filepath);
		// Just a helper func to read from a text file for the functions above
		static std::string readFileToChar(const std::string _filepath);
	};
}

#endif

