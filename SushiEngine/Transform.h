#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "Component.h"
#include "Macros.h"

/** The transfrom component holds all the variables required to transform the gameobject in various ways */

namespace SushiEngine
{
	class Transform : public Component
	{
	public:
		// position of the object in world space
		vec3* mPosition;
		// rotation of the ojbect in world space
		vec3* mRotation;
		// scale of the object
		vec3* mScale;

		// local position
		vec3* mLocalPosition;
		// local rotation
		vec3* mLocalRotation;

		// Default constructor, positioned at origin, no rotation and a scale of 1 assumed.
		Transform(const SuGameObject* fGameObject, vec3 fPosition = vec3(0,0,0), vec3 fRotation = vec3(0,0,0), vec3 fScale = vec3(1,1,1));
		~Transform();	

		mat4 getMatrix();
	};
}
#endif 