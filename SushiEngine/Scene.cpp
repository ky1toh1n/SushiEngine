#include "Scene.h"

namespace SushiEngine {
	//Constructs a Scene
	Scene::Scene()
	{

	}

	Scene::~Scene() {};

	//Initializes scene by getting window pointer
	void Scene::Initialize(AbstractRenderer* pRenderer) {
		window = GameSceneManager::GetInstance()->getWindowInstance();
		renderer = pRenderer;
	};

	//Polls GLFW Events
	void Scene::Update()
	{
		glfwPollEvents();
	}

	//Swaps GLFW Buffers
	void Scene::Render()
	{
		renderer->render();
	}
}