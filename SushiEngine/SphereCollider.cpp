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


	class BoxCollider : public ColliderImpl<BoxCollider> {};
	bool SphereCollider::dispatchOverlapsWith(const BoxCollider &b) const
	{
		return overlaps(b);
	}

	bool SphereCollider::dispatchOverlapsWith(const SphereCollider &s) const
	{
		//Find square distance between spheres
		//glm::length()  is an alternative.
		vec3 difference = (position - s.position);
		float distance = difference.x * difference.x
			+ difference.y * difference.y
			+ difference.z * difference.z;

		//Subtract by both sphere radii squared.
		distance -= (size * size + s.size * s.size);

		//If distance is negative, they are overlapping. 
		return distance < 0;
	}
}
