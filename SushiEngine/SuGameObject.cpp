#include "SuGameObject.h"

namespace SushiEngine {

	SuGameObject::SuGameObject(vec3 _position)
	{
		components = new vector(Component);
		Component* comp = new Component(this);
		//Transform * transform = new Transform(this, _position);
		//components->push_back(*transform);

		position = _position;
	}


	SuGameObject::~SuGameObject()
	{
	}

	void SuGameObject::AddComponent(Component _component)
	{
		components->push_back(_component);
	}
	
	void SuGameObject::Render() {
		mesh->Use();
		texture->Use();

		glDrawArrays(GL_QUADS, 0, 16);
	}

}