#ifndef SCENE_GRAPH_TEST_SCENE_H
#define SCENE_GRAPH_TEST_SCENE_H

#include "Scene.h"
#include "Debug.h"

using namespace SushiEngine;

class SceneGraphTestScene : public Scene
{
public:
	SceneGraphTestScene();
	virtual ~SceneGraphTestScene();
	void initialize(SceneContext* pSceneContext);
	void destroy();
};

#endif