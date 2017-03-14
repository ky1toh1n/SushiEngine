/* A cube collider. */
#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H
/* SushiEngine */
#include "Collider.h"
#include "SphereCollider.h"
/* ---- */
namespace SushiEngine
{
	class BoxCollider : public ColliderImpl<BoxCollider>
	{
	public:
		/* Instance fields */
		// Represents the center of the cube.
		vec3 position;
		// A size of 1 means this cube has a length, width, and height of 1.
		float size;

		/* Constructor */
		BoxCollider(const SuGameObject * fGameObject,
			const vec3 & fPosition,
			const float & fSize);
		~BoxCollider();

		/* Instance methods */
		virtual bool dispatchOverlapsWith(const BoxCollider &b) const;
		virtual bool dispatchOverlapsWith(const SphereCollider &s) const;
	};
}
#endif
