#include "Transform.h"

namespace SushiEngine
{
	Transform::Transform(const SuGameObject * _gameObject, vec3 _position, vec3 _rotation, vec3 _scale) : Component(_gameObject)
	{
		mPosition = new vec3(_position);
		mLocalPosition = new vec3(_position);
		mRotation = new vec3(_rotation);
		mLocalRotation = new vec3(_rotation);
		mScale = new vec3(_scale);
		mLocalScale = new vec3(_scale);
	}

	Transform::~Transform()
	{
		DELETE_PTR(mPosition)
		DELETE_PTR(mLocalPosition)
		DELETE_PTR(mRotation)
		DELETE_PTR(mLocalRotation)
		DELETE_PTR(mScale)
		DELETE_PTR(mLocalScale)
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