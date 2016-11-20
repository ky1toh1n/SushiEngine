/** A singleton class that 'runs' the current game scene. */
#ifndef GAME_H
#define GAME_H 
/* System */
#include <memory>
/* Third Party */
/* SushiEngine */
#include "Debug.h"
#include "Scene.h"
#include "SceneContext.h"
#include "Timer.h"
#include "Macros.h"
/* ---- */
namespace SushiEngine
{
	class GameSceneManager
	{
	public:
		/* Instance methods */
		void run(Scene*);
		InputManager* getInput();

		/* Static methods */
		static GameSceneManager* GetInstance();
	private:
		/* Constructor */
		GameSceneManager();
		~GameSceneManager();
		NO_COPY_CONSTRUCTORS(GameSceneManager)

			/* Instance fields */
			bool mIsRunning;
		Scene * mCurrentScene;
		SceneContext * mSceneContext;

		/* Instance methods */
		bool initialize();
		void update(float _deltaTime);
		void render();
		void destroy();

		/* Static fields */
		static std::unique_ptr<GameSceneManager> sGameInstance;
		// Smart pointer needs to be able to delete GameSceneManager
		friend std::default_delete<GameSceneManager>;
	};
}
#endif
