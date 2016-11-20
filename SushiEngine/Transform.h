/** The transform component holds a gameobject's position, rotation and scale.*/
#ifndef TRANSFORM_H
#define TRANSFORM_H
/* SushiEngine */
#include "Component.h"
#include "Macros.h"
/* ---- */
namespace SushiEngine
{
	class Transform : public Component
	{
	public:
		/* Instance fields */
		// position of the object in world space
		vec3* mPosition;
		// rotation of the ojbect in world space
		quat* mRotation;
		// scale of the object
		vec3* mScale;

		/* Constructor */
		// Default constructor, positioned at origin, no rotation and a scale of 1 assumed.
		Transform(const SuGameObject* fGameObject, vec3 fPosition = vec3(0,0,0), quat fRotation = quat(0,0,0,0), vec3 fScale = vec3(1,1,1));
		~Transform();	

		/* Instance methods */
		mat4 getMatrix();
	};
}
#endif 