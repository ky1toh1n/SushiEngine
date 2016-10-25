//TestScene - Represents a concrete scene to test with.
#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "Scene.h"

class TestScene : public SushiEngine::Scene
{
public:
	TestScene();
	~TestScene();

	void Destroy();
};
#endif
