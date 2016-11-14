#ifndef SU_GAME_OBJECT_H
#define SU_GAME_OBJECT_H

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

#include "Macros.h"
#include "Component.h"
#include "Transform.h"

namespace SushiEngine 
{
	class SuGameObject
	{
	public:
		// a list of the components this gameobject holds
		vector<Component*> components;

		vec3 position;

		SuGameObject(vec3 _position);
		~SuGameObject();
		// adds a component to the component list
		void AddComponent(Component * _component);
		// HIGHLY EXPERIMENTAL, disregard
		//Component* GetComponent(Component _componentType);
		void Render();
	};
}

#endif

