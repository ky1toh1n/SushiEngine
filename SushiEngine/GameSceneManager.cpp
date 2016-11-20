#include "GameSceneManager.h"

namespace SushiEngine
{
	//Initialize singleton
	std::unique_ptr<GameSceneManager> GameSceneManager::sGameInstance(nullptr);

	//Returns the instance; creates it if not exists yet
	GameSceneManager* GameSceneManager::GetInstance()
	{
		if (sGameInstance == nullptr)
		{
			sGameInstance.reset(new GameSceneManager());
		}
		return sGameInstance.get();
	}

	//Creates the GameSceneManager.
	GameSceneManager::GameSceneManager()
	{
		Debug::Log(EMessageType::S_INFO, "GameSceneManager()", __FILENAME__, __LINE__);
	}

	//Destroys the GameSceneManager.
	GameSceneManager::~GameSceneManager()
	{
		Debug::Log(EMessageType::S_INFO, "~GameSceneManager()", __FILENAME__, __LINE__);

		delete(mSceneContext);
		delete(mCurrentScene);
	}

	//Initialzes all the data and context for a game scene to function.
	bool GameSceneManager::initialize()
	{
		Debug::Log(EMessageType::S_INFO, "GameSceneManager() Initialize", __FILENAME__, __LINE__);

		// Instantiate scene context 
		mSceneContext = new SceneContext(u8"Hau5tastic", 720, 720);

		return true;
	}

	//Initializes and runs the game. Contains the main loop.
	void GameSceneManager::run(Scene* pStartingScene)
	{
		//Initialize the game scene manager & current scene.
		mIsRunning = initialize();
		mCurrentScene = pStartingScene;
		mCurrentScene->initialize(mSceneContext);

		//Used to get Delta Time
		Timer timer;
		timer.start();		
		
		//The main loop of the whole program.
		while (mIsRunning)
		{
			//Update & Render
			update((float)(timer.update()));
			render();

			//Gracefully shutdown when requested
			if (glfwWindowShouldClose(mSceneContext->window->GetWindowHandle()))
			{
				destroy();
			}
		}
	}

	//Updates the current scene
	void GameSceneManager::update(float pDeltaTime)
	{
		mCurrentScene->update(pDeltaTime);
	}

	//Renders the current scene.
	void GameSceneManager::render()
	{
		mCurrentScene->render();
	}

	//Returns the InputManager
	InputManager* GameSceneManager::getInput()
	{
		return mSceneContext->input;
	}

	//Cleans up Game Scene Manager.
	void GameSceneManager::destroy()
	{
		mCurrentScene->destroy();
		mSceneContext->destroy();
		mIsRunning = false;
	}
}
