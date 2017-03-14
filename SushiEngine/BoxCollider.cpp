#include "BoxCollider.h"

namespace SushiEngine
{
	BoxCollider::BoxCollider(const SuGameObject * fGameObject,
		const vec3 & fPosition,
		const float & fSize) : ColliderImpl(fGameObject)
		, position(fPosition)
		, size(fSize)
	{

	}

	BoxCollider::~BoxCollider()
	{
	}

	bool BoxCollider::dispatchOverlapsWith(const BoxCollider &b) const
	{
		// Define each cube's min and max point
		vec3 box1Min = position - size / 2;
		vec3 box1Max = position + size / 2;
		vec3 box2Min = b.position - b.size / 2;
		vec3 box2Max = b.position + b.size / 2;

		// Check for that overlap yo
		return (box1Max.x >= box2Min.x &&
			box1Min.x <= box2Max.x &&
			box1Max.y >= box2Min.y &&
			box1Min.y <= box2Max.y &&
			box1Max.z >= box2Min.z &&
			box1Min.z <= box2Max.z);
	}

	bool BoxCollider::dispatchOverlapsWith(const SphereCollider &s) const
	{
		// Define the box's min and max point
		vec3 boxMin = position - size / 2;
		vec3 boxMax = position + size / 2;

		// Get point closest to sphere's center.
		float x = glm::max(boxMin.x, glm::min(s.position.x, boxMax.x));
		float y = glm::max(boxMin.y, glm::min(s.position.y, boxMax.y));
		float z = glm::max(boxMin.z, glm::min(s.position.z, boxMax.z));

		// Get distance from this point to sphere's center
		float distance = sqrt(
			(x - s.position.x) * (x - s.position.x) +
			(y - s.position.y) * (y - s.position.y) +
			(z - s.position.z) * (z - s.position.z));

		// It's overlapping if the distance is within the radius of the sphere
		return distance <= s.size;
	}
}
