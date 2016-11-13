#include "SuGameObject.h"

namespace SushiEngine {

	SuGameObject::SuGameObject(vec3 _position)
	{
		components = new vector<Component>;
		Transform * transform = new Transform(this, _position);
		components->push_back(*transform);

		position = _position;
	}


	SuGameObject::~SuGameObject()
	{
	}

	void SuGameObject::AddComponent(Component _component)
	{
		components->push_back(_component);
	}

	// HIGHLY EXPERIMENTAL
	//Component * SuGameObject::GetComponent(Component _componentType)
	//{
	//	Component* _component = nullptr;

	//	vector(Component)::iterator _iterator = components->begin();

	//	for (int i = 0; i < components->size(); i++)
	//	{
	//		if (typeid(_iterator) == typeid(_componentType))
	//		{
	//			_component = &components->at(i);
	//		}
	//	}

	//	Debug::Log(EMessageType::S_ERROR, "Could not find component.", __FILENAME__, __LINE__);
	//	return _component;
	//}
	
	void SuGameObject::Render() {
		mesh->Use();
		texture->Use();

		glDrawArrays(GL_QUADS, 0, 16);
	}

}