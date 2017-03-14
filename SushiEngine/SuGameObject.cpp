#include "SuGameObject.h"

namespace SushiEngine 
{
	// prototype
	SuGameObject::SuGameObject()
	{
		//Force the compiler to create templated functions of every existing Component Type,
		//by 'fake' calling the functions here.
		//This function should NEVER be called.
		Debug::Log(EMessageType::S_ERROR, "SuGameObject() Private Constructor called.", __FILENAME__, __LINE__);
		AddComponent<Transform>(nullptr);
		GetComponent<Transform>();
		AddComponent<MeshRenderer>(nullptr);
		GetComponent<MeshRenderer>();

		AddComponent<Collider>(nullptr);
		GetComponent<Collider>();
	}

	SuGameObject::SuGameObject(vec3 pPosition)
	{
		Transform * _transform = new Transform(this, pPosition);
		AddComponent<Transform>(_transform);
	}

	SuGameObject::~SuGameObject()
	{
		mComponents.clear();
	}

	template <typename T>
	void SuGameObject::AddComponent(Component * pComponent)
	{
		mComponents.insert(std::make_pair(typeid(T).name(), pComponent));
	}

	template <typename T>
	T* SuGameObject::GetComponent()
	{
		// casting from base class (component) to child class :{D
		return dynamic_cast<T*>(mComponents[typeid(T).name()]);
	}
	
	void SuGameObject::AddGameObject(SuGameObject * _gameObject)
	{
		// add transform parent gameobject transform values to child gameobject
		*_gameObject->GetComponent<Transform>()->mPosition += *(GetComponent<Transform>()->mPosition);
		*_gameObject->GetComponent<Transform>()->mRotation += *(GetComponent<Transform>()->mRotation);
		*_gameObject->GetComponent<Transform>()->mScale *= *(GetComponent<Transform>()->mScale);
		// set the parent object to this gameobject
		_gameObject->mParent = this;
		// add it to the list
		mGameObjects.push_back(_gameObject);
	}

	vector<SuGameObject*> * SuGameObject::GetGameObjects()
	{
		return &mGameObjects;
	}

	void SuGameObject::Render() {

	}

}