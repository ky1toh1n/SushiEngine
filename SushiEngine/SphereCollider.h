/* A sphere collider. */
#ifndef SPHERE_COLLIDER_H
#define SPHERE_COLLIDER_H
/* SushiEngine */
#include "Collider.h"
/* ---- */
namespace SushiEngine
{
	class SphereCollider : public ColliderImpl<SphereCollider>
	{
	public:
		/* Instance fields */
		vec3 position;
		float size;

		/* Constructor */
		SphereCollider(const SuGameObject * fGameObject,
			const vec3 & fPosition,
			const float & fSize);
		~SphereCollider();

		/* Instance methods */
		virtual bool dispatchOverlapsWith(const BoxCollider &b) const;
		virtual bool dispatchOverlapsWith(const SphereCollider &s) const;
	};
}
#endif
