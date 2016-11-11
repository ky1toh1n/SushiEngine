#ifndef  SU_MESH_H
#define SU_MESH_H
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <fstream>
#include <string>
#include "Debug.h"

namespace SushiEngine
{
	class SuMesh
	{

	public:
		SuMesh(const std::string filename);
		bool ImportModel(const std::string filename);
		~SuMesh();

		const aiScene* scene;
		Assimp::Importer importer;
	};
}
#endif // ! SU_MESH_H