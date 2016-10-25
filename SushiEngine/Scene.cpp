#include "Scene.h"

namespace SushiEngine {
	//Constructs a Scene
	Scene::Scene()
	{

	}

	Scene::~Scene() {};

	//Initializes scene by getting window pointer
	void Scene::Initialize() {
		_window = GameSceneManager::GetInstance()->getWindowInstance();
	};

	//Polls GLFW Events
	void Scene::Update()
	{
		glfwPollEvents();
	}

	//Swaps GLFW Buffers
	void Scene::Render()
	{
		glfwSwapBuffers(_window->GetWindowHandle());
	}
}