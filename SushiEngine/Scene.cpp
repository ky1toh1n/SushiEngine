#include "Scene.h"

namespace SushiEngine
{
	//Constructs a Scene
	Scene::Scene()
	{
		Debug::Log(EMessageType::S_INFO, "\tScene()", __FILENAME__, __LINE__);
	}

	Scene::~Scene() 
	{
		Debug::Log(EMessageType::S_INFO, "\t~Scene()", __FILENAME__, __LINE__);
	}

	//Initializes scene by getting window pointer
	void Scene::Initialize(AbstractRenderer* pRenderer) 
	{
		Debug::Log(EMessageType::S_INFO, "\tScene::Initialize()", __FILENAME__, __LINE__);
		window = GameSceneManager::GetInstance()->getWindowInstance();
		mainCamera = new Camera(vec3(0,0,20), vec3(0,1,0));
		renderer = pRenderer;
		renderer->setCamera(mainCamera);

		// SuMesh ananas = SuMesh("models/ananas.fbx");
	}

	//Polls GLFW Events
	void Scene::Update(float deltaTime)
	{
		
		/*Poll for input*/
		glfwPollEvents();
		
		/*Handle Camera Controls.*/
#define ENABLE_CAMERA
		///TODO: Add Delta Time/Chrono PLEASE :"(
#ifdef ENABLE_CAMERA
		InputManager * input = InputManager::GetInstance();
		
		//Translation
		float translateX = (float)(input->isKeyDown(GLFW_KEY_A) ? 1 : 0
			+ input->isKeyDown(GLFW_KEY_D) ? -1 : 0) * deltaTime;
		float translateY = (float)(input->isKeyDown(GLFW_KEY_W) ? -1 : 0
			+ input->isKeyDown(GLFW_KEY_S) ? 1 : 0) * deltaTime;

		mainCamera->translate(translateX, translateY);

		//Rotation
		int screenWidth, screenHeight;
		window->GetSize(&screenWidth, &screenHeight);

		double mouseX, mouseY;
		input->getMousePosition(&mouseX, &mouseY);

		//If mouse is within the screenWidth-ish area of the screen
		if (mouseX >= screenWidth / 2 - screenWidth / 10 &&
			mouseX <= screenWidth / 2 + screenWidth / 10 &&
			mouseY >= screenHeight / 2 - screenHeight / 10 &&
			mouseY <= screenHeight / 2 + screenHeight / 10)
		{
			//Do nothing
			return;
		}
		else 
		{
			//Otherwise, let's rotate!
			float rotateX = float(mouseX - screenWidth / 2) / (float)screenWidth / 1 * deltaTime;
			float rotateY = float(mouseY - screenHeight / 2) / (float)screenHeight / -1 * deltaTime;

			mainCamera->rotate(rotateX, rotateY);
		}
#endif 
	}

	//Swaps GLFW Buffers
	void Scene::Render()
	{
		renderer->render();
	}
}