#ifndef SU_GAME_OBJECT_H
#define SU_GAME_OBJECT_H

#include "SuMesh.h"
#include "SuTexture.h"


namespace SushiEngine {
	class SuGameObject
	{
	public:
		SuGameObject();
		~SuGameObject();

	private:
		const SuMesh* mesh;

		// TODO: Should be 'material' later on
		const SuTexture* texture;
	};

}

#endif

