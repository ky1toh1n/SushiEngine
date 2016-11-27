#include "SceneGraphTestScene.h"

SceneGraphTestScene::SceneGraphTestScene()
{
}


SceneGraphTestScene::~SceneGraphTestScene()
{
}

void SceneGraphTestScene::Initialize(AbstractRenderer * abstractRenderer)
{
	Scene::Initialize(abstractRenderer);

	SuGameObject* box = new SuGameObject(vec3(1.0f, 0.0f, 0.0f));
	Transform* boxt = box->GetComponent<Transform>();
	boxt->mRotation = new vec3(0.0f, 0.0f, 0.0f);

	box->modelId = ModelManager::LoadModel("models/Crate/Crate1.3ds");
	glDisableVertexArrayAttrib(*box->modelId, 2);
	box->textureId = ModelManager::LoadTexture("models/Crate/crate_1.jpg");

	SuGameObject* box2 = new SuGameObject(vec3(1.0f, 1.0f, 1.0f));
	Transform* box2t = box2->GetComponent<Transform>();
	box->AddGameObject(box2);

	cout << "position: " << box2t->mPosition->x << ", " << box2t->mPosition->y << ", " << box2t->mPosition->z << endl;
	cout << "localposition: " << box2t->mLocalPosition->x << ", " << box2t->mLocalPosition->y << ", " << box2t->mLocalPosition->z << endl;
}

void SceneGraphTestScene::Destroy()
{
}