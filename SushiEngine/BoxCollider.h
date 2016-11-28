#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include "Collider.h"
#include "SphereCollider.h"

namespace SushiEngine
{
	class BoxCollider : public ColliderImpl<BoxCollider>
	{
	public:
		vec3 position;
		float size;

		BoxCollider(const SuGameObject * fGameObject,
			const vec3 & fPosition,
			const float & fSize);
		~BoxCollider();

		virtual bool dispatchOverlapsWith(const BoxCollider &b) const;
		virtual bool dispatchOverlapsWith(const SphereCollider &s) const;
	};
}
#endif
