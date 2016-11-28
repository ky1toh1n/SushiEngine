#ifndef MODEL_TEST_SCENE_H
#define MODEL_TEST_SCENE_H

#include "Scene.h"
#include "Debug.h"
#include "MeshRenderer.h"

using namespace SushiEngine;

class ModelTestScene :
	public Scene
{
public:
	ModelTestScene();
	virtual ~ModelTestScene();

	void initialize(SceneContext* pSceneContext);
	void destroy();
	void update(float _deltaTime);
};

#endif