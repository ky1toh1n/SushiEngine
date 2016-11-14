#include "GameSceneManager.h"

namespace SushiEngine
{
	/// See the header file reguarding unique_ptr
	std::unique_ptr<GameSceneManager> GameSceneManager::gameInstance(nullptr);

	//Creates the GameSceneManager.
	GameSceneManager::GameSceneManager() 
	{
		Debug::Log(EMessageType::S_INFO, "GameSceneManager()", __FILENAME__, __LINE__);
	}

	//Destroys the GameSceneManager.
	GameSceneManager::~GameSceneManager() 
	{
		Debug::Log(EMessageType::S_INFO, "~GameSceneManager()", __FILENAME__, __LINE__);

		delete(window);
		delete(renderer);
	}

	//Updates the current scene and handles if the user has attempted to close the window.
	void GameSceneManager::Update(float deltaTime)
	{
		currentScene->Update();
	}

	//Renders the current scene.
	void GameSceneManager::Render()
	{
		currentScene->Render();
	}

	//Returns the current lkan Renderer Initialized.instance of the GameSceneManager.
	GameSceneManager* GameSceneManager::GetInstance() 
	{
		if (gameInstance == nullptr)
		{
			gameInstance.reset(new GameSceneManager());
		}		
		return gameInstance.get();
	}

	//Forward declaration for window callbacks
	static void CloseWindowCallback(GLFWwindow* glfwWindow);
	static void ResizeWindowCallback(GLFWwindow* window, int width, int height);

	//Initialzes all the components necessary for a game scene to function properly.
	bool GameSceneManager::Initialize()
	{
		Debug::Log(EMessageType::S_INFO, "GameSceneManager() Initialize", __FILENAME__, __LINE__);
		
		//Instantiate main components - order is important; a renderer is dependent on a window
		window = new Window("Hau5tastic", 300, 300);
		renderer = new OpenGLRenderer(window);

		//initialize glfw callbacks
		glfwSetWindowUserPointer(window->GetWindowHandle(), this);
		glfwSetWindowCloseCallback(window->GetWindowHandle(), CloseWindowCallback);
		glfwSetWindowSizeCallback(window->GetWindowHandle(), ResizeWindowCallback);

		// Key and Character are both for Keyboard Event Polling, see documentation for the difference between the two.
		glfwSetKeyCallback(window->GetWindowHandle(), InputManager::KeyCallback);
		// glfwSetCharCallback(glfwWindow, character_callback);
		glfwSetMouseButtonCallback(window->GetWindowHandle(), InputManager::ClickCallback);
		glfwSetCursorPosCallback(window->GetWindowHandle(), InputManager::MouseMoveCallback);
		return true;

	}
	
	//Initializes and runs the game. Contains the main loop.
	void GameSceneManager::Run(Scene* startingScene)
	{
		isRunning = Initialize();
		currentScene = startingScene;
		currentScene->Initialize(renderer);

		//Used to get Delta Time/Control Frame Rate [TODO: Make it work.]
		Timer timer;
		unsigned int fps = 60;
		float spf = (float)(1 / fps);
		float delay = 0.0f;
		timer.Start();

		//Used for FPS debugging
		double timeElapsed = 0;
		int frames = 0;

		//The main loop of the whole program.
		while (isRunning)
		{
			timer.UpdateFrameTicks();
			float deltaTime = (float)timer.GetDeltaTime();

			Update(deltaTime);
			Render();

			//Calculating FPS
			timeElapsed += deltaTime;
			frames++;
			if (timeElapsed >= 1) 
			{
				// std::cout << "\nfps: " << frames;
				frames = 0;
				timeElapsed = 0;
			}

			//Gracefully shutdown scene and window
			if (glfwWindowShouldClose(window->GetWindowHandle()))
			{
				currentScene->Destroy();
				window->Destroy();
				isRunning = false;
			}
		}
	}
	
	//Returns the window instance.
	Window* GameSceneManager::getWindowInstance()
	{
		return window;
	}

	// ---- Callback Functions ---
	static void CloseWindowCallback(GLFWwindow* glfwWindow) 
	{
		glfwSetWindowShouldClose(glfwWindow, GLFW_TRUE);
	}

	static void ResizeWindowCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0,0, width, height);
	}
}
