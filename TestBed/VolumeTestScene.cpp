#include "VolumeTestScene.h"

using namespace SushiEngine;

VolumeTestScene::VolumeTestScene()
{
	Debug::Log(EMessageType::S_INFO, "\tVolumeTestScene()", __FILENAME__, __LINE__);
}

VolumeTestScene::~VolumeTestScene()
{
	Debug::Log(EMessageType::S_INFO, "\t~VolumeTestScene()", __FILENAME__, __LINE__);
}

void VolumeTestScene::Initialize(AbstractRenderer* abstractRenderer) {
	Scene::Initialize(abstractRenderer);
	
	Collider * c0 = new Sphere();
	Collider * c1 = new Box();

	c0->overlaps(*c0);
	c0->overlaps(*c1);
	c1->overlaps(*c0);
	c1->overlaps(*c1);

}

void VolumeTestScene::Destroy() {

}
