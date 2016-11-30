/**	This is the base component class that all other components will inherit from. 
* The component system works very similar to unity's component system. */
#ifndef COMPONENT_H
#define COMPONENT_H
/* ---- */
namespace SushiEngine
{
	class SuGameObject;
	class Component
	{
	public:
		// Reference to the gameObject that owns this component.
		const SuGameObject* mGameObject;

		/* Constructors */
		/* 
		* Creates a component object and gets the reference to it's owner.
		* @params fGameObject - A reference to the gameobject that owns this component.
		*
		* Usage in a SuGameObject class:
		* Component* c = new Component(this);
		*/
		Component(const SuGameObject * fGameObject);
		virtual ~Component();	
	};
}
#endif