#include "SuGameObject.h"

namespace SushiEngine 
{
	SuGameObject::SuGameObject(vec3 _position)
	{
		Transform * transform = new Transform(this, _position);
		AddComponent<Transform>(transform);
	}

	SuGameObject::~SuGameObject()
	{
		components.clear();
	}

	template <typename T>
	void SuGameObject::AddComponent(Component *_component)
	{
		components.insert(std::make_pair(typeid(T).name(), _component));
		// getcomponent must be called here for every type of component to be added to the map
		GetComponent<T>();
	}

	template <typename T>
	T* SuGameObject::GetComponent()
	{
		// casting from base class (component) to child class :{D
		return dynamic_cast<T*>(components[typeid(T).name()]);
	}
	
	void SuGameObject::Render() {
	}

}