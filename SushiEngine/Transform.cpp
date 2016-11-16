#include "Transform.h"

namespace SushiEngine
{
	Transform::Transform(const SuGameObject * fGameObject, vec3 fPosition, quat fRotation, vec3 fScale) : Component(fGameObject)
	{
		mPosition = new vec3(fPosition);
		mRotation = new quat(fRotation);
		mScale = new vec3(fScale);
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
		return mat4(1);
	}
}