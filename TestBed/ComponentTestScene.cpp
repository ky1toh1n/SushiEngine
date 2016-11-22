#include "ComponentTestScene.h"

ComponentTestScene::ComponentTestScene()
{
	Debug::LogConstructor("ComponentTestScene", __FILENAME__, __LINE__);
}


ComponentTestScene::~ComponentTestScene()
{
	Debug::LogDeconstructor("ComponentTestScene", __FILENAME__, __LINE__);
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
