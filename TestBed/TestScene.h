//TestScene - Represents a concrete scene to test with.
#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "Scene.h"
#include "Debug.h"

using namespace SushiEngine;

class TestScene : public SushiEngine::Scene
{
public:
	TestScene();
	~TestScene();
	void Initialize(AbstractRenderer* abstractRenderer);
	void Destroy();
};
#endif
