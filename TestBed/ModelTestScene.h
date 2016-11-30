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

	SuGameObject *sun, *mercury, *venus, *earth, *mars, *jupiter, *saturn, *uranus, *neptune;
	Transform *sunTransform, *mercuryTransform, *venusTransform, *earthTransform, *marsTransform, *jupiterTransform, *saturnTransform, *uranusTransform, *neptuneTransform;

	float speedMultiplier = 1.0f;
	bool pause = false;
	float elapsed = 0.0f;
};

#endif