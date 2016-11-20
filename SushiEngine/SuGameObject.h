/** Represents a visible entity in a Game Scene.
* Components can be added to customize the game objects.
*/
#ifndef SU_GAME_OBJECT_H
#define SU_GAME_OBJECT_H
/* Third Party */
#include <GL\glew.h>
/* SushiEngine */
#include "Macros.h"
#include "Component.h"
#include "Transform.h"
#include "MeshRenderer.h"
/* ---- */
namespace SushiEngine 
{
	class SuGameObject
	{
	public:
		/* Constructor */
		SuGameObject(vec3 fPosition);
		~SuGameObject();

		/* Instance methods */
		// adds a component to the component list
		template<typename T>
		void AddComponent(Component * fComponent);
		// gets a component from the component list
		template<typename T>
		T* GetComponent();
		void Render();

		// ModelImporter Tests
		const GLuint* modelId = nullptr;
		const GLuint* textureId = nullptr;
	protected:
		/* Instance fields */
		// a list of the components this gameobject holds
		unordered_map<string, Component*> mComponents;
	private:
		/* Constructor */
		// Not meant to be called; see definition for details
		SuGameObject();
	};
}
#endif