#include "SuGameObject.h"

namespace SushiEngine 
{
	// prototype
	SuGameObject::SuGameObject(vec3 _position)
	{
		Transform * transform = new Transform(this, _position);
		AddComponent<Transform>(transform);
		GetComponent<Transform>();
		MeshRenderer * houseMesh = new MeshRenderer(this, "models/Crate/Crate1.3ds");
		AddComponent<MeshRenderer>(houseMesh);
		GetComponent<MeshRenderer>();
	}

	SuGameObject::~SuGameObject()
	{
		components.clear();
	}

	template <typename T>
	void SuGameObject::AddComponent(Component *_component)
	{
		components.insert(std::make_pair(typeid(T).name(), _component));
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