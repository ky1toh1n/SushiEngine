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

		bool Initialize();

		VkRenderer* renderer;
		bool isRunning;
		GameSceneManager();
		virtual ~GameSceneManager();
		Window* window;
		Scene* currentScene;

	public:
		static GameSceneManager* GetInstance();
		void Run();
		virtual void Update();
		virtual void Render();

		void HandleInput(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
		void HandleClick(GLFWwindow* glfwWindow, int button, int action, int mods);

	};
}
#endif