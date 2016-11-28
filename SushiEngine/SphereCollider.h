#ifndef SPHERE_COLLIDER_H
#define SPHERE_COLLIDER_H

#include "Collider.h"

namespace SushiEngine
{
	class SphereCollider : public ColliderImpl<SphereCollider>
	{
	public:
		vec3 position;
		float size;

		SphereCollider(const SuGameObject * fGameObject,
			const vec3 & fPosition,
			const float & fSize);
		~SphereCollider();

		virtual bool dispatchOverlapsWith(const BoxCollider &b) const;
		virtual bool dispatchOverlapsWith(const SphereCollider &s) const;
	};
}
#endif
