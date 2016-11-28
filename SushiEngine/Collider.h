#ifndef COLLIDER_H
#define COLLIDER_H

#include <iostream>

#include "Debug.h"
#include "Macros.h"
#include "SuGameObject.h"
#include "Component.h"

namespace SushiEngine
{
	class BoxCollider;
	class SphereCollider;
	template <typename T>
	class ColliderImpl;

	class Collider : public Component
	{
	public:
		Collider(const SuGameObject * fGameObject) : Component(fGameObject)
		{

		}
		virtual bool overlaps(const Collider &) const = 0;
	protected:
		template <typename T>
		friend class ColliderImpl;
		virtual bool dispatchOverlapsWith(const BoxCollider &) const = 0;
		virtual bool dispatchOverlapsWith(const SphereCollider &) const = 0;
	};

	template <typename T>
	class ColliderImpl : public Collider
	{

	public:
		ColliderImpl(const SuGameObject * fGameObject) : Collider(fGameObject)
		{

		}
		virtual bool overlaps(const Collider &o) const
		{
			//assert(typeid(*this) == typeid(T));
			return o.dispatchOverlapsWith(static_cast<const T&>(*this));
		}
	};
}
#endif