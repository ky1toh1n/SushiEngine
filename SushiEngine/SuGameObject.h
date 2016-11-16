#ifndef SU_GAME_OBJECT_H
#define SU_GAME_OBJECT_H

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

#include "Macros.h"
#include "Component.h"
#include "Transform.h"

#include "GL\glew.h"


namespace SushiEngine 
{
	class SuGameObject
	{
	public:
		vec3 position;

		SuGameObject(vec3 _position);
		~SuGameObject();

		// adds a component to the component list
		template<typename T>
		void AddComponent(Component * _component);

		// gets a component from the component list
		template<typename T>
		T* GetComponent();

		void Render();

		// ModelImporter Tests
		const GLuint* modelId;

	protected:
		// a list of the components this gameobject holds
		unordered_map<string, Component*> components;

	};
}

#endif

