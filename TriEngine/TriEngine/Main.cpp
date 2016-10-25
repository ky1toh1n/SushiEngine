#include "Main.h"

using namespace TriEngine;

int main(int, char**) {

	// Only continue if computer is on 32-bit operating system
	static_assert(sizeof(void*) == 4, "Code-base is designed for 32-bit architectures.");



	Debug::Init();
	Debug::Log(EMessageType::INFO, "PROGRAM START On Main.cpp", __FILENAME__, __LINE__);

	Game* stadium = Game::GetInstance();
	stadium->Run();

	Debug::Log(EMessageType::INFO, "PROGRAM EXIT on Main.cpp", __FILENAME__, __LINE__);

	return 0;
}