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



	SuGameObject* box = new SuGameObject(vec3(0.0f, 0.0f, 0.0f));
	Transform* t = box->GetComponent<Transform>();

	box->modelId = ModelManager::LoadModel("models/Crate/Crate1.3ds");
	box->textureId = ModelManager::LoadTexture("models/Crate/RTS_Crate.png");

	glBindBuffer(GL_ARRAY_BUFFER, *box->modelId);
	glBindTexture(GL_TEXTURE_2D, *box->textureId);

}

void TestScene::Destroy() {

}
