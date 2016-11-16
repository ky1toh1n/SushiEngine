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

void TestScene::Initialize(AbstractRenderer* abstractRenderer) {
	Scene::Initialize(abstractRenderer);

	SuGameObject box = SuGameObject(vec3(1.0f, 10.0f, 9.0f));
	Transform* t = box.GetComponent<Transform>();
	cout << t->mPosition->y << endl;
}

void TestScene::Destroy() {

}
