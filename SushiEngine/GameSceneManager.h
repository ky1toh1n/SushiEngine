// GameSceneManager : Manages the current game Scene. It ensures that there's only one active Scene at a time.
#ifndef GAME_H
#define GAME_H

#include <memory>
#include "VkRenderer.h"
#include "Debug.h"
#include "Window.h"
#include "Scene.h"

namespace SushiEngine 
{
	class GameSceneManager
	{
	private:
		///std::unique_ptr is a smart pointer that destroys the object it point to when the unique_ptr goes out of scope.
		static std::unique_ptr<GameSceneManager> gameInstance;

		/// Since my destructor is private the template std::unique_ptr needs access so I made it a friend.
		/// However, std::default_delete is the default destruction policy used by std::unique_ptr 
		/// when no deleter is specified, therefore I'll make std::default_delete my friend as well. 
		friend std::default_delete<GameSceneManager>;

		//Private constructor
		GameSceneManager();
		virtual ~GameSceneManager();

		//Private fields
		bool isRunning;
		Scene *currentScene;
		Window* window;
		VkRenderer* renderer;

		//Private methods
		bool Initialize();
		void Update();
		void Render();
	public:		
		//Public interface
		static GameSceneManager* GetInstance();
		Window* getWindowInstance();
		//TODO: Find a way to specify the starting scene through type specifier. 
		void Run();

		//TODO: move this to Input Manager
		void HandleInput(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
		void HandleClick(GLFWwindow* glfwWindow, int button, int action, int mods);

		/// C11 precautions delete these non-needed default constructors and operators
		GameSceneManager(const GameSceneManager&) = delete;
		GameSceneManager(GameSceneManager&&) = delete;
		GameSceneManager& operator = (const GameSceneManager&) = delete;
		GameSceneManager& operator = (GameSceneManager&&) = delete;
	};
}
#endif