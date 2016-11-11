#include "SuGameObject.h"

namespace SushiEngine {

	SuGameObject::SuGameObject(glm::vec3 _position)
	{
		position = _position;
	}


	SuGameObject::~SuGameObject()
	{
	}
	

	void SuGameObject::Render() {
		mesh->Use();
		texture->Use();

		glDrawArrays(GL_QUADS, 0, 16);
	}

}