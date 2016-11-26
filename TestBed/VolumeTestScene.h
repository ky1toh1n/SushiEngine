//VolumeTestScene- Represents a concrete scene to test with.
#ifndef VOLUME_TEST_SCENE_H
#define VOLUME_TEST_SCENE_H

#include "Scene.h"
#include "Debug.h"
#include "Collider.h"

using namespace SushiEngine;

class VolumeTestScene: public SushiEngine::Scene
{
public:
	VolumeTestScene();
	~VolumeTestScene();
	void Initialize(AbstractRenderer* abstractRenderer);
	void Destroy();
};
#endif
