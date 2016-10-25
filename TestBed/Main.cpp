#include "GameSceneManager.h"
#include "TestScene.h"

int main(int count, char** args) {
	SushiEngine::Debug::Init();
	SushiEngine::GameSceneManager* game = SushiEngine::GameSceneManager::GetInstance();

	game->Run(new TestScene());

	return 0;
}
