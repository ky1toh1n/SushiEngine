#ifndef COMPONENT_TEST_SCENE_H
#define COMPONENT_TEST_SCENE_H

#include "Scene.h"
#include "Debug.h"
#include "SuGameObject.h"

using namespace SushiEngine;

class ComponentTestScene : public Scene
{
public:
	ComponentTestScene();
	virtual ~ComponentTestScene();
	void initialize(SceneContext* pSceneContext);
	void destroy();
};

#endif