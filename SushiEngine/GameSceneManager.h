// GameSceneManager : Manages the current game Scene. It ensures that there's only one active Scene at a time.
#ifndef GAME_H
#define GAME_H

#include <memory>
#include "VRenderer.h"
#include "Debug.h"
#include "Window.h"
#include "InputManager.h"
#include "Scene.h"
#include "Timer.h"

namespace SushiEngine 
{
	class Scene;

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
		VRenderer* renderer;

		//Private methods
		bool Initialize();
		void Update(float deltaTime);
		void Render();
	public:		
		//Public interface
		static GameSceneManager* GetInstance();
		Window* getWindowInstance();
		void Run(Scene*);

		/// C11 precautions delete these non-needed default constructors and operators
		GameSceneManager(const GameSceneManager&) = delete;
		GameSceneManager(GameSceneManager&&) = delete;
		GameSceneManager& operator = (const GameSceneManager&) = delete;
		GameSceneManager& operator = (GameSceneManager&&) = delete;
	};
}
#endif