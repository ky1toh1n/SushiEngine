#ifndef COMPONENT_H
#define COMPONENT_H

class SuGameObject;

namespace SushiEngine
{
	class Component
	{
	public:
		const SuGameObject* mGameObject;

		Component(SuGameObject * _gameObject);
		virtual ~Component();
	protected:
		
	};
}
#endif