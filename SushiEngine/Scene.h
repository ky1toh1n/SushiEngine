//Scene - Represents a playable scene in a game. Concrete scenes must extend this abstract class.
#ifndef SCENE_H
#define SCENE_H

#include "Window.h"
#include "GameSceneManager.h"

namespace SushiEngine {
	class Scene
	{
	public:
		//Constructor
		Scene();
		virtual ~Scene() = 0;
		
		/// C11 precautions delete these non-needed default constructors and operators
		Scene(const Scene&) = delete;
		Scene(Scene&&) = delete;
		Scene& operator = (const Scene&) = delete;
		Scene& operator = (Scene&&) = delete;

		//Main methods of a scene
		virtual void Initialize();
		virtual void Update();
		virtual void Render();
		virtual void Destroy() = 0;

	protected:
		//
		Window * _window;
	};
}
#endif