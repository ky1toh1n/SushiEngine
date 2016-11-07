#include "GameSceneManager.h"
#include "TestScene.h"


const int TESTBED_VERSION_NUMBER = 0b00000111;

int main(int count, char** args) {
	SushiEngine::Debug::Init();
	SushiEngine::GameSceneManager* game = SushiEngine::GameSceneManager::GetInstance();

	game->Run(new TestScene());

	getchar();

	return 0;
}
