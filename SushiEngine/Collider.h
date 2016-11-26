#ifndef COLLIDER_H
#define COLLIDER_H

#include <iostream>

#include "Debug.h"
#include "Macros.h"
#include "SuGameObject.h"
#include "Component.h"

namespace SushiEngine
{
	class Box;
	class Sphere;
	template <typename T>
	class ColliderImpl;

	class Collider : public Component
	{
	public:
		Collider(const SuGameObject * fGameObject) : Component(fGameObject)
		{

		}
		virtual void overlaps(const Collider &o) const = 0;
	protected:
		template <typename T>
		friend class ColliderImpl;
		virtual void dispatchOverlapsWith(const Box &b) const = 0;
		virtual void dispatchOverlapsWith(const Sphere &b) const = 0;
	};

	template <typename T>
	class ColliderImpl : public Collider
	{

	public:
		ColliderImpl(const SuGameObject * fGameObject) : Collider(fGameObject)
		{

		}
		virtual void overlaps(const Collider &o) const
		{
			//assert(typeid(*this) == typeid(T));
			return o.dispatchOverlapsWith(static_cast<const T&>(*this));
		}
	};

	class Box : public ColliderImpl<Box>
	{
	public:
		Box(const SuGameObject * fGameObject) : ColliderImpl(fGameObject)
		{
			
		}
	protected:
		virtual void dispatchOverlapsWith(const Box &b) const
		{
			cout << "Box on box baby." << endl;
		}

		virtual void dispatchOverlapsWith(const Sphere &b) const
		{

			cout << "Box on sphere baby." << endl;
		}
	};


	class Sphere : public ColliderImpl<Sphere>
	{
	public:
		Sphere(const SuGameObject * fGameObject) : ColliderImpl(fGameObject)
		{

		}
	protected:
		virtual void dispatchOverlapsWith(const Box &b) const
		{
			//cout << "Sphere on box baby." << endl;
			overlaps(b);
		}

		virtual void dispatchOverlapsWith(const Sphere &b) const
		{
			cout << "Sphere on sphere baby." << endl;
		}
	};
}
#endif