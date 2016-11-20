/** Represents a playable (and abstract) scene in a game.*/
#ifndef SCENE_H
#define SCENE_H
/* System */
/* Third Party */
/* SushiEngine */
#include "SceneContext.h"
#include "Camera.h"
#include "Macros.h"
/* ---- */
namespace SushiEngine
{
	class Scene
	{
	public:
		/* Constructor */
		Scene();
		virtual ~Scene() = 0;
		NO_COPY_CONSTRUCTORS(Scene)

		/* Instance Methods */
		virtual void initialize(SceneContext*);
		virtual void update(float deltaTime);
		virtual void render();
		virtual void destroy() = 0;
	protected:
		/* Instance Fields */
		SceneContext * mSceneContext;
		Camera * mMainCamera;
		vector<SuGameObject*> mGameObjects;
	};
}
#endif