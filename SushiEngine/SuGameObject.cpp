#include "SuGameObject.h"

namespace SushiEngine 
{
	// prototype
	SuGameObject::SuGameObject()
	{
		Transform * _transform = new Transform(this, vec3(1.0f, 1.0f, 1.0f));
		AddComponent<Transform>(_transform);
		GetComponent<Transform>();

		MeshRenderer * _houseMesh = new MeshRenderer(this, "models/Crate/Crate1.3ds");
		AddComponent<MeshRenderer>(_houseMesh);
		GetComponent<MeshRenderer>();
	}

	SuGameObject::SuGameObject(vec3 fPosition)
	{
		Transform * _transform = new Transform(this, fPosition);
		AddComponent<Transform>(_transform);
	}

	SuGameObject::~SuGameObject()
	{
		mComponents.clear();
	}

	template <typename T>
	void SuGameObject::AddComponent(Component * fComponent)
	{
		mComponents.insert(std::make_pair(typeid(T).name(), fComponent));
	}

	template <typename T>
	T* SuGameObject::GetComponent()
	{
		// casting from base class (component) to child class :{D
		return dynamic_cast<T*>(mComponents[typeid(T).name()]);
	}
	
	void SuGameObject::AddGameObject(SuGameObject * _gameObject)
	{
		mGameObjects.push_back(_gameObject);
	}

	vector<SuGameObject*> * SuGameObject::GetGameObjects()
	{
		return &mGameObjects;
	}

	void SuGameObject::Render() {
	}

}