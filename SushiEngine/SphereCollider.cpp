#include "SphereCollider.h"

namespace SushiEngine
{
	SphereCollider::SphereCollider(const SuGameObject * fGameObject,
		const vec3 & fPosition,
		const float & fSize) : ColliderImpl(fGameObject)
		, position(fPosition)
		, size(fSize)
	{

	}

	SphereCollider::~SphereCollider()
	{
	}


	// Forward declare that BoxCollider inherits from ColliderImpl.,
	// so that it can be casted to a Collider in overlaps().
	class BoxCollider : public ColliderImpl<BoxCollider> {};
	bool SphereCollider::dispatchOverlapsWith(const BoxCollider &b) const
	{
		//We rely on BoxCollider to implement Box-Sphere collision detection.
		//This causes some circular dependency issues, which is solved by the dark
		//forward declaration above.
		return overlaps(b);
	}

	bool SphereCollider::dispatchOverlapsWith(const SphereCollider &s) const
	{
		//Find square distance between spheres
		//glm::length()  is an alternative.
		vec3 difference = (position - s.position);
		float distance = glm::length(difference);

		//Subtract by both sphere radii squared.
		distance -= (size * size + s.size * s.size);

		//If distance is negative, they are overlapping. 
		return distance <= 0;
	}
}
