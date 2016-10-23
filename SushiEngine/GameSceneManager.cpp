#include "GameSceneManager.h"

namespace SushiEngine
{
	/// See the header file reguarding unique_ptr
	std::unique_ptr<GameSceneManager> GameSceneManager::gameInstance(nullptr);

	GameSceneManager::GameSceneManager() {
		Debug::Log(EMessageType::INFO, "GameSceneManager() Created", __FILENAME__, __LINE__);
	}

	GameSceneManager::~GameSceneManager() {
		Debug::Log(EMessageType::INFO, "GameSceneManager() Destroyed", __FILENAME__, __LINE__);
		glfwTerminate();
		delete renderer;
	}

	void GameSceneManager::Update()
	{
		currentScene->Update();

		if (glfwWindowShouldClose(window->GetWindowHandle())) {
			window->Shutdown();
			isRunning = false;
		}
	}

	void GameSceneManager::Render()
	{
		currentScene->Render();
	}

	GameSceneManager* GameSceneManager::GetInstance() {
		if (gameInstance == nullptr) {
			gameInstance.reset(new GameSceneManager());
		}

		return gameInstance.get();
	}

	static void CloseWindowCallback(GLFWwindow* glfwWindow);
	static void KeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
	static void ClickCallback(GLFWwindow* glfwWindow, int button, int action, int mods);

	bool GameSceneManager::Initialize()
	{
		Debug::Log(EMessageType::INFO, "GameSceneManager() Initialize", __FILENAME__, __LINE__);
		
		renderer = new VkRenderer();

		window = new Window();
		window->Initialize();
		window->SetTitle("HI");
		window->SetSize(640, 480);

		//initialize glfw callbacks
		glfwSetWindowUserPointer(window->GetWindowHandle(), this);
		glfwSetWindowCloseCallback(window->GetWindowHandle(), CloseWindowCallback);

		// Key and Character are both for Keyboard Event Polling, see documentation for the difference between the two.
		glfwSetKeyCallback(window->GetWindowHandle(), KeyCallback);
		// glfwSetCharCallback(glfwWindow, character_callback);
		glfwSetMouseButtonCallback(window->GetWindowHandle(), ClickCallback);



		return true;
	}

	void GameSceneManager::Run()
	{
		isRunning = Initialize();
		currentScene = new Scene(window);

		while (isRunning)
		{
			Update();
			Render();
		}

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
