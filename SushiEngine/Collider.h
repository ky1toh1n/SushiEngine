/* A base collider component made up of two classes.
 * It uses templates to implement double dispatch.
 * All existing collider types and methods must be declared in this file.
 */
#ifndef COLLIDER_H
#define COLLIDER_H
 /* System */
#include <iostream>
/* SushiEngine */
#include "Debug.h"
#include "Macros.h"
#include "SuGameObject.h"
#include "Component.h"
/* ---- */
namespace SushiEngine
{
	/* Forward declarations */
	class BoxCollider;
	class SphereCollider;
	template <typename T>
	class ColliderImpl;
	/* ---- */
	class Collider : public Component
	{
	public:
		/* Constructor */
		Collider(const SuGameObject * fGameObject) : Component(fGameObject) {};

		/* Instance methods */
		virtual bool overlaps(const Collider &o) const = 0;
	protected:
		/* Instance methods */
		virtual bool dispatchOverlapsWith(const BoxCollider &b) const = 0;
		virtual bool dispatchOverlapsWith(const SphereCollider &b) const = 0;

		//Friending is used to access 'dispatchOverlaps' of other colliders
		template <typename T>
		friend class ColliderImpl;
	};
	/* ---- */
	template <typename T>
	class ColliderImpl : public Collider
	{

	public:
		/* Constructor */
		ColliderImpl(const SuGameObject * fGameObject) : Collider(fGameObject) {};

		/* Instance methods */
		///I don't know how to move this magical code to a .cpp file. =m=//
		virtual bool overlaps(const Collider &o) const
		{
			return o.dispatchOverlapsWith(static_cast<const T&>(*this));
		};
	};
}
#endif