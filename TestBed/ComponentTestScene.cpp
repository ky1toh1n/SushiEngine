#include "ComponentTestScene.h"

ComponentTestScene::ComponentTestScene()
{
	Debug::Log(EMessageType::S_INFO, "\tComponentTestScene()", __FILENAME__, __LINE__);
}


ComponentTestScene::~ComponentTestScene()
{
	Debug::Log(EMessageType::S_INFO, "\t~ComponentTestScene()", __FILENAME__, __LINE__);
}

void ComponentTestScene::initialize(SceneContext* pSceneContext)
{
	Scene::initialize(pSceneContext);

	SuGameObject box = SuGameObject(vec3(1.0f, 10.0f, 9.0f));
	Transform* t = box.GetComponent<Transform>();
	cout << t->mPosition->y << endl;
}

void ComponentTestScene::destroy() {

}
