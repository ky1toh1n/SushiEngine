#include "Transform.h"

namespace SushiEngine
{
	Transform::Transform(const SuGameObject * fGameObject) : Component(fGameObject)
	{
		mPosition = new vec3(0.0f, 0.0f, 0.0f);
		mRotation = new quat(0.0f, 0.0f, 0.0f, 0.0f);
		mScale = new vec3(1.0f, 1.0f, 1.0f);
	}

	Transform::Transform(const SuGameObject * fGameObject, vec3 fPosition) : Component(fGameObject)
	{
		mPosition = &fPosition;
		mRotation = new quat(0.0f, 0.0f, 0.0f, 0.0f);
		mScale = new vec3(1.0f, 1.0f, 1.0f);
	}

	Transform::Transform(const SuGameObject * fGameObject, vec3 fPosition, quat fRotation) : Component(fGameObject)
	{
		mPosition = &fPosition;
		mRotation = &fRotation;
		mScale = new vec3(1.0f, 1.0f, 1.0f);
	}

	Transform::Transform(const SuGameObject * fGameObject, vec3 fPosition, quat fRotation, vec3 fScale) : Component(fGameObject)
	{
		mPosition = &fPosition;
		mRotation = &fRotation;
		mScale = &fScale;
	}

	Transform::~Transform()
	{
		delete mPosition;
		mPosition = nullptr;
		delete mRotation;
		mRotation = nullptr;
		delete mScale;
		mScale = nullptr;
	}


	mat4 Transform::getMatrix()
	{
		//TODO: Implement this function. How the f**k do we use quaternions to rotate, House?!

		//Rotate then translate.

		//TODO: Then Scale.
	}
}