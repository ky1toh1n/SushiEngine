#include "GameSceneManager.h"
#include "Scene.h"
#include "VkRenderer.h"

int main(int count, char** args) {
	SushiEngine::Debug::Init();
	SushiEngine::GameSceneManager* game = SushiEngine::GameSceneManager::GetInstance();

	game->Run();

	return 0;
}