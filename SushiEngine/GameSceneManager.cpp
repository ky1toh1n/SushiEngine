#include "GameSceneManager.h"

namespace SushiEngine
{
	/// See the header file reguarding unique_ptr
	std::unique_ptr<GameSceneManager> GameSceneManager::gameInstance(nullptr);

	//Creates the GameSceneManager.
	GameSceneManager::GameSceneManager() {
		Debug::Log(EMessageType::S_INFO, "GameSceneManager() Created", __FILENAME__, __LINE__);
	}

	//Destroys the GameSceneManager.
	GameSceneManager::~GameSceneManager() {
		Debug::Log(EMessageType::S_INFO, "GameSceneManager() Destroyed", __FILENAME__, __LINE__);

		delete(window);
		delete(renderer);
	}

	//Updates the current scene and handles if the user has attempted to close the window.
	void GameSceneManager::Update()
	{
		currentScene->Update();

		//Gracefully shutdown scene and window
		if (glfwWindowShouldClose(window->GetWindowHandle())) {
			currentScene->Destroy();
			window->Destroy();
			isRunning = false;
		}
	}

	//Renders the current scene.
	void GameSceneManager::Render()
	{
		currentScene->Render();
	}

	//Returns the current instance of the GameSceneManager.
	GameSceneManager* GameSceneManager::GetInstance() {
		if (gameInstance == nullptr) {
			gameInstance.reset(new GameSceneManager());
		}		return gameInstance.get();
	}

	static void CloseWindowCallback(GLFWwindow* glfwWindow);
	static void KeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
	static void ClickCallback(GLFWwindow* glfwWindow, int button, int action, int mods);

	//Initialzes all the components necessary for a game scene to function properly.
	bool GameSceneManager::Initialize()
	{
		Debug::Log(EMessageType::S_INFO, "GameSceneManager() Initialize", __FILENAME__, __LINE__);
		
		//Instantiate main components - order is important; a renderer is dependent on a window
		window = new Window("Hau5tastic", 300, 300);
		renderer = new VkRenderer();

		//initialize glfw callbacks
		glfwSetWindowUserPointer(window->GetWindowHandle(), this);
		glfwSetWindowCloseCallback(window->GetWindowHandle(), CloseWindowCallback);

		// Key and Character are both for Keyboard Event Polling, see documentation for the difference between the two.
		glfwSetKeyCallback(window->GetWindowHandle(), KeyCallback);
		// glfwSetCharCallback(glfwWindow, character_callback);
		glfwSetMouseButtonCallback(window->GetWindowHandle(), ClickCallback);

		return true;
	}
	
	//Initializes and runs the game. Contains the main loop.
	void GameSceneManager::Run()
	{
		isRunning = Initialize();
		currentScene = new Scene(window);

		//The main loop of the whole program.
		while (isRunning)
		{
			//Update must be after Render, because the window closing code happens in Update. Otherwise, the code will crash at Render.
			Render();
			Update();
		}
	}
	
	//Returns the window instance.
	Window* GameSceneManager::getWindowInstance() {
		return window;
	}

	// TODO: Create an abstraction between InputHandling and the Game Class
	void GameSceneManager::HandleInput(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_W && action == GLFW_PRESS) {
			Debug::Print("Pressed W");
		}
	}

	void GameSceneManager::HandleClick(GLFWwindow* window, int button, int action, int mods) {
		Debug::Print("Click!");
	}

	// ---- Callback Functions ---
	static void CloseWindowCallback(GLFWwindow* glfwWindow) {
		glfwSetWindowShouldClose(glfwWindow, GLFW_TRUE);
	}

	static void KeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
		//Game* game = reinterpret_cast<Game*>(glfwGetWindowUserPointer(glfwWindow));
		GameSceneManager::GetInstance()->HandleInput(glfwWindow, key, scancode, action, mods);
	}

	static void ClickCallback(GLFWwindow* glfwWindow, int button, int action, int mods) {
		//Game* game = reinterpret_cast<Game*>(glfwGetWindowUserPointer(glfwWindow));
		GameSceneManager::GetInstance()->HandleClick(glfwWindow, button, action, mods);
	}
}
