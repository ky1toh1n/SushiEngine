#include "TestScene.h"

using namespace SushiEngine;

TestScene::TestScene()
{
	Debug::Log(EMessageType::S_INFO, "\tTestScene()", __FILENAME__, __LINE__);
}

TestScene::~TestScene()
{
	Debug::Log(EMessageType::S_INFO, "\t~TestScene()", __FILENAME__, __LINE__);
}

void TestScene::initialize(SceneContext* pSceneContext)
{
	Scene::initialize(pSceneContext);
}

void TestScene::destroy() {

}
