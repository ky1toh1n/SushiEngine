//Scene - Represents a playable scene in a game. Concrete scenes must extend this abstract class.
#ifndef SCENE_H
#define SCENE_H

#include "Window.h"

namespace SushiEngine {
	class Scene
	{
	public:
		//
		explicit Scene(Window *);
		virtual ~Scene()/* = 0*/;
		
		/// C11 precautions delete these non-needed default constructors and operators
		Scene(const Scene&) = delete;
		Scene(Scene&&) = delete;
		Scene& operator = (const Scene&) = delete;
		Scene& operator = (Scene&&) = delete;

		//
		virtual void Initialize()/* = 0*/;
		virtual void Update();
		virtual void Render();
		virtual void Destroy()/* = 0*/;

	protected:
		//
		Window * _window;
	};
}
#endif