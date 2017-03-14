#include "TestScene.h"

using namespace SushiEngine;

TestScene::TestScene()
{
	Debug::LogConstructor("TestScene", __FILENAME__, __LINE__);
}

TestScene::~TestScene()
{
	Debug::LogDeconstructor("TestScene", __FILENAME__, __LINE__);
}

void TestScene::initialize(SceneContext* pSceneContext)
{
	Scene::initialize(pSceneContext);
}

void TestScene::destroy() {

}
