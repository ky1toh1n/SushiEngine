#ifndef SCENE_H
#define SCENE_H
#include "Window.h"

namespace SushiEngine {
	class Scene
	{
	public:
		Scene(Window* window);
		~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

	private:
		Window * _window;
	};
}
#endif