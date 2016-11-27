#include "GameSceneManager.h"

#include "TestScene.h"
#include "ComponentTestScene.h"
#include "ModelTestScene.h"
#include "SceneGraphTestScene.h"

using namespace SushiEngine;

const int TESTBED_VERSION_NUMBER = 0b00000111;

int main(int count, char** args) {
	Debug::Init();
	GameSceneManager* game = GameSceneManager::GetInstance();

	Scene* scene;

	//scene = new TestScene();
	//scene = new ComponentTestScene();
	//scene = new ModelTestScene();
	scene = new SceneGraphTestScene();

	game->Run(scene);

	DELETE_PTR(scene)
	
	getchar();
	return 0;
}
