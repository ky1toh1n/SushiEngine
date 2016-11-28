#include "Transform.h"

namespace SushiEngine
{
	Transform::Transform(const SuGameObject * pGameObject, vec3 pPosition, vec3 pRotation, vec3 pScale) : Component(pGameObject)
	{
		mPosition = new vec3(pPosition);
		mRotation = new vec3(pRotation);
		mScale = new vec3(pScale);
	}

	Transform::~Transform()
	{
		DELETE_PTR(mPosition)
		DELETE_PTR(mRotation)
		DELETE_PTR(mScale)
	}


	mat4 Transform::getMatrix()
	{
		//TODO: Implement this function. How the f**k do we use quaternions to rotate, House?!
		// FFS learn to rotate :{X
		// *cries*

		//Rotate then translate.

		//TODO: Then Scale.
		return mat4(1);
	}
}