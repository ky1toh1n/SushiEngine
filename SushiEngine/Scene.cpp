#include "Scene.h"

namespace SushiEngine {
	Scene::Scene(Window* window) : _window(window)
	{

	}

	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{

	}

	void Scene::Update()
	{
		glfwPollEvents();
	}

	void Scene::Render()
	{
		glfwSwapBuffers(_window->GetWindowHandle());
	}
}