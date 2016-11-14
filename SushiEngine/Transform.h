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
		quat* mRotation;
		// scale of the object
		vec3* mScale;

		// Default constructor, positioned at origin, no rotation and a scale of 1 assumed.
		Transform(const SuGameObject* fGameObject);
		Transform(const SuGameObject* fGameObject, vec3 fPosition);
		Transform(const SuGameObject* fGameObject, vec3 fPosition, quat fRotation);
		Transform(const SuGameObject* fGameObject, vec3 fPosition, quat fRotation, vec3 fScale);
		~Transform();	

		mat4 getMatrix();
	};
}
#endif 