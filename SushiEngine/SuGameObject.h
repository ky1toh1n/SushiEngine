#ifndef SU_GAME_OBJECT_H
#define SU_GAME_OBJECT_H

#include "Macros.h"
#include "Component.h"
#include "Transform.h"
#include "MeshRenderer.h"

#include "GL\glew.h"

namespace SushiEngine 
{
	class SuGameObject
	{
	public:
		SuGameObject(vec3 fPosition);
		~SuGameObject();

		// adds a component to the component list
		template<typename T>
		void AddComponent(Component * fComponent);

		// gets a component from the component list
		template<typename T>
		T* GetComponent();

		void Render();

	protected:
		// a list of the components this gameobject holds
		unordered_map<string, Component*> mComponents;

	private:
		// prototype object, all components must be hashed onto the map for the component system to function properly in external projects
		SuGameObject();
	};
}
#endif