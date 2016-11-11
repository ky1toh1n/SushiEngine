#ifndef SU_GAME_OBJECT_H
#define SU_GAME_OBJECT_H

#include "SuMesh2.h"
#include "SuTexture.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"


namespace SushiEngine {
	class SuGameObject
	{
	public:
		SuGameObject(glm::vec3 _position);
		~SuGameObject();

		glm::vec3 position;
		void Render();

		SuMesh2* mesh;

		// TODO: Should be 'material' later on
		SuTexture* texture;
	};

}

#endif

