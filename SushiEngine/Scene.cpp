#include "Scene.h"

namespace SushiEngine
{
	//Constructs a Scene
	Scene::Scene()
	{
		Debug::LogConstructor("Scene", __FILENAME__, __LINE__);
		Debug::sTabLevel++;
	}

	Scene::~Scene() 
	{
		Debug::sTabLevel--;
		Debug::LogDeconstructor("Scene", __FILENAME__, __LINE__);
	}

	//Initializes scene with a scene context
	void Scene::initialize(SceneContext* pSceneContext)
	{
		Debug::Log(EMessageType::S_INFO, "\tScene::Initialize()", __FILENAME__, __LINE__);
		mSceneContext = pSceneContext;
		mMainCamera = new Camera(vec3(0, 2, 15), vec3(0, 1, 0));
		mSceneContext->renderer->setCamera(mMainCamera);
	}

	//Polls GLFW Events
	void Scene::update(float pDeltaTime)
	{
		/*Poll for input*/
		glfwPollEvents();
		
		/*Handle Camera Controls.*/
#define ENABLE_CAMERA

#ifdef ENABLE_CAMERA
		InputManager * input = mSceneContext->input;

		//Translation
		float translateX = (float)
			(input->isKeyDown(GLFW_KEY_A) ? 1 : 0
			+ input->isKeyDown(GLFW_KEY_D) ? -1 : 0) * pDeltaTime;
		float translateY = (float)
			(input->isKeyDown(GLFW_KEY_W) ? -1 : 0
			+ input->isKeyDown(GLFW_KEY_S) ? 1 : 0) * pDeltaTime;

		mMainCamera->translate(translateX, translateY);

		//Rotation
		int screenWidth, screenHeight;
		mSceneContext->window->GetSize(&screenWidth, &screenHeight);

		double mouseX, mouseY;
		mSceneContext->input->getMousePosition(&mouseX, &mouseY);

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
			float rotateX = float(mouseX - screenWidth / 2) / (float)screenWidth / 1 * pDeltaTime;
			float rotateY = float(mouseY - screenHeight / 2) / (float)screenHeight / -1 * pDeltaTime;

		mMainCamera->rotate(rotateX, rotateY);
		}
#endif 
	}

	//Draw the whole scene
	void Scene::render()
	{
		mSceneContext->renderer->render(mGameObjects);
	}
}