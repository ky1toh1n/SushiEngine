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
	void Initialize(AbstractRenderer* abstractRenderer);
	void Destroy();
	void Update(float _deltaTime);
};

#endif