#include "ModelTestScene.h"

ModelTestScene::ModelTestScene()
{
	Debug::Log(EMessageType::S_INFO, "\tModelTestScene()", __FILENAME__, __LINE__);
}


ModelTestScene::~ModelTestScene()
{
	Debug::Log(EMessageType::S_INFO, "\t~ModelTestScene()", __FILENAME__, __LINE__);
}

void ModelTestScene::Initialize(AbstractRenderer * abstractRenderer)
{
	Scene::Initialize(abstractRenderer);


	// ModelImporter Tests
	go = new SuGameObject(glm::vec3(0, 0, 0));
	if (!go) cout << "Failed to create GameObject" << endl;
	
	houseMesh = new MeshRenderer(go, "models/house/house.3ds");

	// this break it for some reason
	//go->AddComponent<MeshRenderer>(houseMesh);

}

void ModelTestScene::Destroy()
{
}
